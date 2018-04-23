#include "elev.h"
#include "executive.h"
#include "buttonspressed.h"
#include "input.h"
#include <stdio.h>


void order_placed(void){ //Poller alle knapper og setter verdiene i buttonsPressed til de respektive knappene. 
	for (elev_button_type_t button = BUTTON_CALL_UP; button < 3; button++){
		for (int floor = 0; floor < 4; floor++){
			if((button == BUTTON_CALL_UP && floor == 3) || (button == BUTTON_CALL_DOWN && floor == 0))
			{
				continue;
			}
			if(elev_get_button_signal(button, floor) == 1){
				set_button_pressed(4*button+floor);
			}
		}
	}
	return;
}
