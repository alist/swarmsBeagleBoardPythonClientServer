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
void runSimpleMotorAction(MotorController controller);
extern "C" API_TYPE bool initializeDriveControl(void);


#pragma mark testing:
int getWebBeansInt(int max);
extern "C" API_TYPE void printGreeting(void);


#endif
