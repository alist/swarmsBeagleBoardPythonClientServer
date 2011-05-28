#include <iostream>
#include "driveLib.h"



extern "C" API_TYPE bool initializeDriveControl(void){
	
	MotorController controller;
    controller.open();
	
	runSimpleMotorAction(controller);	
	
	controller.close();
	
	return true;
}



void runSimpleMotorAction(MotorController controller){	
	int issuedCommandsCount = 0;
	
		int i = 0;
		while (i < 200) {
			
			if (i % 2 == 0){
				controller.toggleLed1();	
				issuedCommandsCount ++;
			}else if (i % 5 == 0){
				controller.toggleLed2();
				issuedCommandsCount ++;
				int direction = i -100;
				controller.setDirection(direction);
				issuedCommandsCount ++;				
			}
			printf("issued [%i] commands \n",issuedCommandsCount);
			
			usleep(1000 * 200); //microseconds * 1000 = miliseconds * 100 =  .1 seconds
			i ++;	
		}
}



extern "C" API_TYPE void printGreeting(void){
	std::cout<< "hello from printGreeting of driveLib.so!" << std::endl;
	std::cout<< "your lucky # is: "<<getWebBeansInt(200)<<std::endl;

}


int getWebBeansInt(int max){
	srand ( time(NULL) );
	return rand() % 10 + 1;
}
