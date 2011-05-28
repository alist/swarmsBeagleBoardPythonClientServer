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
	for dir in steerPlot:
		print ('dir: ', dir);
		setDriveControlDirection(dir);
		time.sleep(.1)


initializeDriveControl();
steerPlot = fibSteerList(-100, 100);
runSteerPlot(steerPlot);
steerPlot2 = fibSteerList(0,100);
runSteerPlot(steerPlot2);
steerPlot.reverse();
runSteerPlot(steerPlot);

teardownDriveControl();

