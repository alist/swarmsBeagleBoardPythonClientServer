#include <iostream>
#include "driveLib.h"

void printGreeting(){
	std::cout<< "saying hello from printGreeting of driveLib.so!" << endl;
}

extern "C" API_TYPE void printGreeting();

