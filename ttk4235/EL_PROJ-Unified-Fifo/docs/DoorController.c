#include "DoorController.h"

bool open;

void DC_openDoor(){
	HW_setDoorOpenLamp(1);
	open = true;
}

void DC_closeDoor(){
	HW_setDoorOpenLamp(0);
	open = false;
}

bool DC_isOpen(){
	return open;
}