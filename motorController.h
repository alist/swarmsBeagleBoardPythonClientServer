#ifndef __MOTORCONTROLLER_H__
#define __MOTORCONTROLLER_H__


/*
//	Major development caveats for beagle embedded + swarms 
//	OBSC system does NOT have watchdog timer ensuring a reset after the main motor stutters and jumps voltage because of sliding PWM values 
//		-this is particularly important in non-shared ground situations wherein voltage differentials matter more
//	Once SWARMS registers fill for waiting on OBSC responses, the device hangs indefinitely
 //	OBSC embedded is very touchy, yet can possibly robust in future if able to pureify power reaching device through regulation
 */




#include <usb.h>

#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

class MotorController { 
public:
    MotorController();

    void reset();
    void open();
    void close();

    void toggleLed2();
    void toggleLed1();

    
    void setSpeed(int speed);
    void setDirection(int direction);
   
private:
    int speed_current;
    int direction_current;

    bool sendCommandWithPayload(string command, string payload);
    bool sendSyncronousFrame(string command, string payload);

    usb_dev_handle * usbDeviceHandle;
};

#endif
