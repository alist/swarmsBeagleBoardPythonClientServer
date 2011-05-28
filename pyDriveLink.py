import numpy as N
import ctypes as C
_foo = N.ctypeslib.load_library('libDrive', '.')
_foo.printGreeting.argtypes = None
_foo.printGreeting.restype = C.c_void_p
def printGreeting():
	return _foo.printGreeting();

printGreeting();
