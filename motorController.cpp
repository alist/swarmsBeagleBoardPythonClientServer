#include "motorController.h"

#include "utility.h"

MotorController::MotorController() {
    speed_current = 0;
    direction_current = 0;
}

void MotorController::reset() {
    unsigned int my_vendor = 62680; // F4D8
    unsigned int my_product = 3844; // 0F04

    struct usb_bus * bus;
    struct usb_device * dev;
    
    usb_init(); /* Initialize libusb */
    usb_find_busses(); /* Find all USB busses on system */
    usb_find_devices();     /* Find all devices on all USB devices */
    usb_set_debug(0);

    bool found = false;

    /* usb_busses is a global variable. */
    for (bus = usb_busses; bus; bus = bus->next) {
        for (dev = bus->devices; dev; dev = dev->next) {

            if(dev->descriptor.idVendor == my_vendor &&
               dev->descriptor.idProduct == my_product) {
                found = true;

                break;
            }

        }
        
        if(found) break;
    }

    if(!found) cout << "usb motor controller is not found" << endl;
    assert(found);

    // Opens a USB device
    usbDeviceHandle = usb_open(dev);
    usb_reset(usbDeviceHandle);    

    close();
}

void MotorController::open() {
    reset();

    unsigned int my_vendor = 62680; // F4D8
    unsigned int my_product = 3844; // 0F04

    struct usb_bus * bus;
    struct usb_device * dev;
    
    usb_init(); /* Initialize libusb */
    usb_find_busses(); /* Find all USB busses on system */
    usb_find_devices();     /* Find all devices on all USB devices */
    usb_set_debug(0);

    bool found = false;

    /* usb_busses is a global variable. */
    for (bus = usb_busses; bus; bus = bus->next) {
        for (dev = bus->devices; dev; dev = dev->next) {

            if(dev->descriptor.idVendor == my_vendor &&
               dev->descriptor.idProduct == my_product) {
                found = true;

                break;
            }

        }
        
        if(found) break;
    }

    int result;

    if(!found) cout << "usb motor controller is not found" << endl;
    assert(found);

    // Opens a USB device
    usbDeviceHandle = usb_open(dev);
//     reset(usbDeviceHandle);
//     usbDeviceHandle = usb_open(dev);

    if(!usbDeviceHandle) {
        cout << "usb_open failed" << endl;
        close();
        assert(false);
    }

//     result = usb_detach_kernel_driver_np(usbDeviceHandle, 0);
//     if(result == 0)
//         //detach the driver from the kernel , seems to be just like rmmod , but it always returns errors , however , it works
//         cout << "device detached successfully from the kernel" << endl; 
//     else 
//         cout << "error detaching the device (" << result << ")" << endl;    

    // Sets the active configuration of the device
    result = usb_set_configuration(usbDeviceHandle, 1);
    if(result < 0) {
        cout << "usb_set_configuration failed (" << result << ")" << endl;
        close();
        assert(false);
    }

    // claims the interface with the Operating System
    result = usb_claim_interface(usbDeviceHandle, 0);
    if(result < 0) {
        cout << "usb_claim_interface failed (" << result << ")" << endl;

        close();
        assert(false);
    }
    
}

void MotorController::close() {
    usb_close(usbDeviceHandle);    
}

bool MotorController::sendCommandWithPayload(string command, string payload) {
    int packetSize = 64;
    char OutputPacketBuffer[64] = {0}; //Allocate a memory buffer which will contain data to send to the USB device

    string toSendString = "";
    wchar_t payloadLength = 1;
    if (payload.size() > 0 && payload != "") {
        payloadLength = payload.size();
        toSendString = command + (char)payloadLength + payload;

        for (int i = 0; i < toSendString.size(); i++) {
            OutputPacketBuffer[i] = toSendString[i];
			printf ("Byte out #%i: [%i] \n",i,toSendString[i]);
		}
    }
    else {
        payloadLength = 0;
        
        toSendString = command + (char)payloadLength;
        OutputPacketBuffer[0] = toSendString[0];
        OutputPacketBuffer[1] = (char)0;
    }


    if(usb_bulk_write(usbDeviceHandle, 0x01, &OutputPacketBuffer[0], packetSize, 500) != packetSize)
        return false;

    return true;
}

bool MotorController::sendSyncronousFrame(string command, string payload) {
    char InputPacketBuffer[64] = {0}; //Allocate a memory buffer for the data which we will read from the USB device
        
    bool result = sendCommandWithPayload(command, payload);
	
	
	const char *commandChar = NULL;
	commandChar = command.c_str();
	int commandInt = (int)commandChar[0];
    if(result) printf ("command [%i] was sent successfully\n",commandInt);
    else cout << "failed to send with payload" << endl;
    
    wchar_t *tempReceiveChar = (wchar_t*)malloc(255);
    usb_bulk_read(usbDeviceHandle, 0x81, &InputPacketBuffer[0], 64, 200);
    tempReceiveChar[1+InputPacketBuffer[1]] = 0;
    
    if (InputPacketBuffer != 0) {
		cout << "Frame returned data:" <<endl;
        for (int i = 0; i < 2+InputPacketBuffer[1];i++) { 
            tempReceiveChar[i] = InputPacketBuffer[i];
			printf ("Byte in #%i: [%i] \n",i,InputPacketBuffer[i]);
        }
    }

    return (tempReceiveChar[0] == 1);
}

void MotorController::toggleLed2() {
    string command, payload;
    command += (char)5;
    payload += (char)2;
    
    bool returned = sendSyncronousFrame(command, payload);
    
    assert(returned);
}

void MotorController::toggleLed1() {
    string command, payload;
    command += (char)5;
    payload += (char)1;
    
    bool returned = sendSyncronousFrame(command, payload);
    
    assert(returned);
}


/// Set the speed of the motor to 'speed' in the integer range [-100, 100]
///
void MotorController::setSpeed(int speed) {
//     if(speed == speed_current)
//         return;

    string command, payload;
    command += (char)19;
    string speed_str = Utility::intToString(speed);
    payload += speed_str;

    bool returned = sendSyncronousFrame(command, payload);
    assert(returned);

    speed_current = speed;
}

/// Set the direction of the steering in the integer range [-100, 100]
///
void MotorController::setDirection(int direction) {
//     if(direction == direction_current)
//         return;    
    
    string command, payload;
    command += (char)20;
    string direction_str = Utility::intToString(direction);
    payload += direction_str;
	printf ("Set Direction: [%s] \n",direction_str.c_str());
	
    bool returned = sendSyncronousFrame(command, payload);
    if (returned == false){
		cout << "alert: ignored invalid controller response; check for SWARMS-OBSC COM interference" <<endl;
	}

    direction_current = direction;
}
