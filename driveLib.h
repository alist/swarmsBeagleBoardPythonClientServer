#define BUILD_DLL

#ifndef DRIVELIB
#define DRIVELIB

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <motorController.h>


#if defined (__GNUC__) 
  #define API_TYPE __attribute__ ((__visibility__("default")))
#elif defined (WIN32)

#ifdef BUILD_DLL
#define API_TYPE __declspec(dllexport)
#else
#define API_TYPE __declspec(dllimport)
#endif

#else
#warning "no supported build"
#endif

#pragma mark control
extern "C" API_TYPE bool initializeDriveControl(void);
extern "C" API_TYPE bool setDriveControlDirection(int direction);
extern "C" API_TYPE bool setDriveControlSpeed(int speed);
extern "C" API_TYPE bool teardownDriveControl(void);
extern "C" API_TYPE bool remoteVehicleIsConnected(void);

extern "C" API_TYPE bool testDriveControlSteering(void);
//test
void runSimpleSteerTestAction(MotorController controller);


#pragma mark testing:
int getWebBeansInt(int max);
extern "C" API_TYPE void printGreeting(void);


#endif
