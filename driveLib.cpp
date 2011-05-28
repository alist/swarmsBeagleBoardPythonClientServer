#include <iostream>

#include "driveLib.h"

extern "C" API_TYPE void printGreeting(void){
	std::cout<< "saying hello from printGreeting of driveLib.so!" << std::endl;
	std::cout<< "webBeansIntSays>>:"<<getWebBeansInt(200)<<std::endl;

}


int getWebBeansInt(int max){
	srand ( time(NULL) );
	return rand() % 10 + 1;
}
