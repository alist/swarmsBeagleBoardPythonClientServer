import time 
import numpy as N
import ctypes as C
_foo = N.ctypeslib.load_library('libDrive', '.')
_foo.printGreeting.argtypes = None
_foo.printGreeting.restype = C.c_void_p
def printGreeting():
	return _foo.printGreeting();

printGreeting();

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
	initializeDriveControl();
	steerPlot = fibSteerList(-100, 100);
	runSteerPlot(steerPlot);
	steerPlot2 = fibSteerList(0,100);
	runSteerPlot(steerPlot2);
	steerPlot.reverse();
	runSteerPlot(steerPlot);
	teardownDriveControl();
	

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
	print "%s wrote:" % self.client_address[0]
        print self.data;        # just send back the same data, but upper-cased
        self.request.send(self.data.upper())
	if self.data == "driveTest;":
		print ('test driveMODE')
		testRunDrive();

import commands
CURRENTIP = commands.getoutput("ifconfig").split("\n")[1].split()[1][5:]

HOST, PORT = "192.168.1.100", 7337
if CURRENTIP == HOST:

	# if an outside host isn't used, eg not localhost, then the port is not opened to the outside world	
	server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)

	# Activate the server; this will keep running until you
	# interrupt the program with Ctrl-C
	server.serve_forever()
else:
	print ('Server is not associated with default address: ',HOST,' but instead: ',CURRENTIP);
