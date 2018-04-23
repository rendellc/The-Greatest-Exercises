#include "HW_driver.h"
#include "FloorDetector.h"

static int lastFloor = -1;

int FD_getFloor(void) {
	int temp = HW_getFloorSensorSignal(); // returns -1 if not on floor

	if (temp+1 != 0) { // true if temp = 0,1,2,3
		lastFloor = temp;
	}
	
	return lastFloor;
}

bool volatile FD_isOnFloor(void) {
	return (HW_getFloorSensorSignal() != -1);
}
