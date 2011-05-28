import numpy as N
import ctypes as C
_foo = N.ctypeslib.load_library('libDrive', '.')
_foo.printGreeting.argtypes = None
_foo.printGreeting.restype = C.c_void_p
def printGreeting():
	return _foo.printGreeting();

printGreeting();

print('Testing USB lib');

_foo.initializeDriveControl.argtypes = None
_foo.initializeDriveControl.restype = C.c_bool

def initializeDriveControl():
	return _foo.initializeDriveControl();

initializeDriveControl();

