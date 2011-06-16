import time 
import numpy as N
import ctypes as C
import os

os.system("/home/root/alex/drivePy/startup/netConfig.sh")

_foo = N.ctypeslib.load_library('libDrive', '.')
_foo.printGreeting.argtypes = None
_foo.printGreeting.restype = C.c_void_p
def printGreeting():
	return _foo.printGreeting();

printGreeting();

_foo.remoteVehicleIsConnected.argtypes = None
_foo.remoteVehicleIsConnected.restype = C.c_bool
def remoteVehicleIsConnected():
	return _foo.remoteVehicleIsConnected();

_foo.initializeDriveControl.argtypes = None
_foo.initializeDriveControl.restype = C.c_bool
def initializeDriveControl():
	return _foo.initializeDriveControl();

_foo.setDriveControlSpeed.argtypes = [C.c_int]
_foo.setDriveControlSpeed.restype = C.c_bool
def setDriveControlSpeed(speed):
	return _foo.setDriveControlSpeed(speed);

_foo.setDriveControlDirection.argtypes = [C.c_int]
_foo.setDriveControlDirection.restype = C.c_bool
def setDriveControlDirection(direction):
	return _foo.setDriveControlDirection(direction);
	
_foo.teardownDriveControl.argtypes = None
_foo.teardownDriveControl.restype = C.c_bool
def teardownDriveControl():
	return _foo.teardownDriveControl();


_foo.testDriveControlSteering.argtypes = None
_foo.testDriveControlSteering.restype = C.c_bool
def testDriveControlSteering():
	return _foo.testDriveControlSteering();
	
	
def fibSteerList(minInt,maxInt):
	steerList	= [];
	a, b		= 0, 1;
	while a < maxInt + (-1) * minInt:
		steerList.append(a + minInt);	# to start at minimum
		a,b		= b, a+b;
	return steerList;

def runSteerPlot(plot):
	for dir in plot:
		print ('dir: ', dir);
		setDriveControlDirection(dir);
		time.sleep(.1)



def testRunDrive():
	steerPlot = fibSteerList(-100, 100);
	runSteerPlot(steerPlot);
	steerPlot2 = fibSteerList(0,100);
	runSteerPlot(steerPlot2);
	steerPlot.reverse();
	runSteerPlot(steerPlot);


def handleRemoteClientCommmand(command, argument):
	if command == None: return
	
	if command == "stop":
		if remoteVehicleIsConnected() == False:
			return "error %(c)s: remote vehicle not connected;" %{"c" : command}

		setDriveControlSpeed(0);
		teardownDriveControl();
	elif command == "start":
		initializeDriveControl();
	elif command == "steer":
		if remoteVehicleIsConnected() == False:
			return "error %(c)s: remote vehicle not connected;" %{"c" : command}
		
		if argument == None:
			return;
		else:
			direction = int(argument);
			if abs(direction) <= 100:
				setDriveControlDirection(direction);
			else:
				return "error steer: value out of bounds;"
	elif command == "drive":
		if remoteVehicleIsConnected() == False:
			return "error %(c)s: remote vehicle not connected;" %{"c" : command}
	
		if argument == None:
			return;
		else:
			speed = int(argument);
			if abs(speed) < 100:
				setDriveControlSpeed(speed);
			else:
				return "error drive: value out of bounds;"
	elif command == "test":
		if remoteVehicleIsConnected() == False:
			return "error %(c)s: remote vehicle not connected;" %{"c" : command}
		
		testRunDrive();
	elif command == "pause":
		time.sleep(.05);
	else:
		error = "error '%(c)s': unknown command '%(c)s' issued with argument '%(a)s';" %{"c" : command, "a" : argument }
		print error;
		return error;
	
	return "did %(c)s %(a)s;" %{"c" : command, "a" : argument }

		
import socket
import threading
import SocketServer

class MyTCPHandler(SocketServer.BaseRequestHandler):
    """
    The RequestHandler class for our server.

    It is instantiated once per connection to the server, and must
    override the handle() method to implement communication to the
    client.
    """

    def handle(self):
        # self.request is the TCP socket connected to the client
        self.data = self.request.recv(1024).strip()
        print "socket input:", self.data;        # just send back the same data, but upper-cased
	commands = self.data.split(';');
	returnString = "";
	os.system("echo 0 > /sys/class/leds/beagleboard\:\:usr1/brightness")
	for command in commands:
		parts		= command.split();
		if len(parts) == 0:
			break
		command		= parts[0];
		argument	= '';
		if len(parts) > 1:
			argument	= parts[1];
		clientRet = handleRemoteClientCommmand(command, argument);
		returnString = returnString + clientRet;
#	print "%s wrote:" % self.client_address[0]
	self.request.send(returnString);
	os.system("echo 1 > /sys/class/leds/beagleboard\:\:usr1/brightness")

import commands
CURRENTIP = commands.getoutput("ifconfig").split("\n")[1].split()[1][5:]

HOST, PORT = "192.168.1.100", 7337
if CURRENTIP == HOST:
	os.system("echo 0 > /sys/class/leds/beagleboard\:\:usr1/brightness")
	# if an outside host isn't used, eg not localhost, then the port is not opened to the outside world	
	server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)

	# Activate the server; this will keep running until you
	# interrupt the program with Ctrl-C
	print ('Server is serving forever at: ',HOST,':',PORT);
	os.system("echo 1 > /sys/class/leds/beagleboard\:\:usr1/brightness")
	server.serve_forever()
else:
	print ('Server is not associated with default address: ',HOST,' but instead: ',CURRENTIP);
	os.system("echo 0 > /sys/class/leds/beagleboard\:\:usr1/brightness")

