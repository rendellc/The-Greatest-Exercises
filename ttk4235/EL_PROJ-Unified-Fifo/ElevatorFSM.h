#pragma once



/*
	Initializes the elevator. If the elevator is not on a floor, ie. inbetween two floors,
	move down, then stop when arrived on a floor.
*/
void EL_initialize();



/*
	Check for CallUp, CallDown, and Command buttonpresses and add them to the appropriate FIFO queue.
	Returns True if buttons have been pressed. Returns False if no buttons have been pressed.
*/
bool EL_checkAndUpdateOrders();



/*
	Updates the Floor indicators to light up at the last visited floor.
*/
void EL_updateFloorIndicators();



/*
	adds the buttons that are in the FIFO queue in to CallUp, CallDown, and Command arrays that keep tabs on what lights to light up.
	Updates the CallUp, callDown, and Command buttonlights.
*/
void EL_updateQueueLights();


/* 	
	return the next floor elevator should move to.
	If no next floor is available, return -1
*/
int EL_getNextFloor();



/*
	Set state according to which direction elevator should move
*/
void EL_gotoFloor(int wantedFloor);



/*
	The main statemachine loop. implements what the state machine should do in each state.
*/
void EL_mainloop();