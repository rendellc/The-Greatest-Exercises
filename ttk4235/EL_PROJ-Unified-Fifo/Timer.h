#pragma once

#include <stdbool.h>

/* 	Start counting down */
void TIMER_start();

/* 	Set time in milliseconds. 
	No input validation. */ 	
void TIMER_set(int msSet);

/*	Return true if more seconds than the set time
	have passed since TIMER_start() was called. 
	Undefined behavior if it is called without TIMER_start()
	having been called. 
*/ 
bool TIMER_timeout();
