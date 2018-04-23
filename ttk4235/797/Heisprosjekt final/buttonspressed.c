#include "elev.h"
#include <stdio.h>

int buttonsPressed[12] = {0}; //[0] til [3] er bestillingsknapper opp, [4] til [7] er ned og [8] til [11] er etasjeknappene.

void clear_orders(void){
	for (int i = 0; i < 12; i++){
		buttonsPressed[i] = 0;
	}
}

void set_button_pressed(int index){
	buttonsPressed[index] = 1;
}

void reset_button_pressed(int index){
	buttonsPressed[index] = 0;
}


int get_button_pressed(int index){
	return buttonsPressed[index];
}

int sum_of_buttons_pressed(void){
	int sum = 0;
	for (int i = 0; i < 12; i++){
		sum += get_button_pressed(i);
	}
	return sum;
}
