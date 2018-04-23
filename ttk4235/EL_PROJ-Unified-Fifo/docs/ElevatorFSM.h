#pragma once



void EL_initialize();


void EL_updateQueueLights();


/* 	return the next floor elevator should move to
	If no next floor is available, return -1
*/
int EL_getNextFloor();

/*	Set state according to which direction elevator should move
*/
void EL_gotoFloor(int wantedFloor);