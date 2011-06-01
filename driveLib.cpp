#include <iostream>
#include "driveLib.h"

extern "C" API_TYPE void printGreeting(void){
	std::cout<< "saying hello from printGreeting of driveLib.so!" << std::endl;
}


