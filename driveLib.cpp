#include <iostream>
#include "driveLib.h"

static MotorController * rcDriveController;


extern "C" API_TYPE bool remoteVehicleIsConnected(void){
	if (rcDriveController == NULL)
		return false;
	
	return rcDriveController->isOpen();
}

extern "C" API_TYPE bool initializeDriveControl(void){
	
	rcDriveController = new MotorController;
	
	rcDriveController->open();
		
	return true;
}


extern "C" API_TYPE bool testDriveControlSteering(void){
	if (rcDriveController == NULL){
		cout << "rcDriveController is not initialized or open \n";
		
		return false;
	}
	runSimpleSteerTestAction(*rcDriveController);	
	
	return true;
}

extern "C" API_TYPE bool teardownDriveControl(void){
	rcDriveController->close();
	delete rcDriveController;
	rcDriveController = NULL;
	
	return true;
}


extern "C" API_TYPE bool setDriveControlDirection(int direction){
	if (rcDriveController == NULL){
		cout << "rcDriveController is not initialized or open \n";
		
		return false;
	}
	
	rcDriveController->setDirection(direction);
	
	return true;
	
}
extern "C" API_TYPE bool setDriveControlSpeed(int speed){	
	if (rcDriveController == NULL){
		cout << "rcDriveController is not initialized or open \n";
		
		return false;
	}
	
	rcDriveController->setSpeed(speed);
	
	return true;
}


void runSimpleSteerTestAction(MotorController controller){	
	int issuedCommandsCount = 0;
	
		int i = 0;
		while (i < 200) {
			
			if (i % 2 == 0){
				controller.toggleLed1();	
				issuedCommandsCount ++;
			}else if (i % 3 == 0){
				controller.toggleLed2();
				issuedCommandsCount ++;
				int direction = i -100;
				controller.setDirection(direction);
				issuedCommandsCount ++;				
			}
			printf("issued [%i] commands \n",issuedCommandsCount);
			
			usleep(1000 * 150); //microseconds * 1000 = miliseconds * 150 =  .15 seconds
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
