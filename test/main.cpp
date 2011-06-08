#include "driveLib.h"
#include <iostream>

int main (void){
printGreeting();
if (remoteVehicleIsConnected()){
	std::cout << "the vehicle is connected!\n";
}else{
	std::cout << "the vehicle is not connected :(\n";
}

return 0;
}
