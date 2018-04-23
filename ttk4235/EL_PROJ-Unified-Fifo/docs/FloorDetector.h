#pragma once
#include <stdbool.h>


/*
  Get floor sensor signal.
  @return -1 if elevator is not on a floor. 0-3 if elevator is on floor. 0 is
    ground floor, 3 is top floor.
*/
int FD_getFloor(void);


/*
	Get if the elevator is on a floor
	@return true(1) if elevator is on a floor.
	false(0) is not on a floor.
*/
bool volatile FD_isOnFloor(void);
