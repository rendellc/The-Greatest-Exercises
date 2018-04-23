#include "DoorController.h"



void DC_openDoor(){
	HW_setDoorOpenLamp(1);
}

void DC_closeDoor(){
	HW_setDoorOpenLamp(0);
}