#include "fsm.h"
#include "qs.h"
#include "elev.h"

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

//Private variable

int current_floor = 0;
int next_floor = 0;
int current_dir = 0;
int last_dir = 0;

int order_table[3][4] ={
// 	1 	2 	3 	4 (Etasjenummer)
	{0, 0, 0, 0},	//Opp-ordre
	{0, 0, 0, 0},	//Ned-ordre
	{0, 0, 0, 0}	//Panel
};

void qs_reset_orders() {

	for (int floor = 0; floor < 4; floor++)
	{
		for (int button = 0; button < 3; button++)
		{
			if (floor == 0 && button == BUTTON_CALL_DOWN) continue;
			if (floor == N_FLOORS-1 && button == BUTTON_CALL_UP) continue;
			order_table[button][floor] = 0;
			elev_set_button_lamp(button,floor,0);
		}
	}

}

int qs_check_orders() {


	//Itererer gjennom knappe-signalene og returnerer dersom en ordre-knapp er trykket inn

	for(int floor = 0; floor < 4; floor++) { 									
		for (int button = 0; button < 3; button++) {
			if (floor == 0 && button == BUTTON_CALL_DOWN) continue;
			if (floor == N_FLOORS-1 && button == BUTTON_CALL_UP) continue;
			if (elev_get_button_signal(button,floor)) {

				if (order_table[button][floor] == 0){

					order_table[button][floor] = 1;
					elev_set_button_lamp(button,floor,1); 	

					if (qs_get_number_of_orders() == 1){
					qs_set_next_floor(floor);
					}

					return 1;
				}

				else{

					elev_set_button_lamp(button,floor,1); 	

					if (qs_get_number_of_orders() == 1){
					qs_set_next_floor(floor);
					continue;

					}
				}
			}
		}
	}

	return 0;

}

int qs_get_below_order() {

	for (int floor = current_floor; floor >= 0; floor--){ //Sjekker for ned- og cab-knapper under heisen
		if (order_table[1][floor] || order_table[2][floor]){
			next_floor = floor;
			return 1;
		}
	}

	for (int floor = 0; floor <= 3; floor++){
		if((order_table[1][floor] == 1 || order_table[0][floor] == 1 || order_table[2][floor])){ //Sjekker resterende knapper på panelet

			next_floor = floor;
			return 1;
		}
	}

	return 0;
}

int qs_get_above_order() {

	for (int floor = current_floor; floor < 4; floor++){ //Sjekker for ned- og cab-knapper over heisen
		//Sjekker om det er opp-ordre eller heispanel-ordre over heisen
		if (order_table[0][floor] || order_table[2][floor] ){
			next_floor = floor;
			//printf("Henter above etasje: %d\n", floor );
			return 1;
		}
	}

	for (int floor = 3; floor >= 0; floor--){
		if((order_table[1][floor] == 1 || order_table[0][floor] == 1 || order_table[2][floor])){ //Sjekker for resterende knapper på panelet

			next_floor = floor;
			return 1;
		}
	}

	return 0;

}


void qs_delete_orders() {
	//Sletter alle ordre i nåværende etasje
	for (int button = 0; button < 3; button++){
		order_table[button][current_floor] = 0;
		if (current_floor == 0 && button == BUTTON_CALL_DOWN) continue;
		if (current_floor == N_FLOORS-1 && button == BUTTON_CALL_UP) continue;
		elev_set_button_lamp(button, current_floor, 0);
	}

}


void qs_set_priority() {
	//Setter prioritet på neste etasje basert på nåværende- og forrige retning heisen kjørte
	if (current_dir == DIRN_UP){
		qs_get_above_order();
		return;
	} else if(current_dir == DIRN_DOWN) {
		qs_get_below_order();
		return;
	} else if(current_dir == 0 && last_dir == DIRN_UP && current_floor != 3) {
		qs_get_above_order();
		return;
	} else if(current_dir == 0 && last_dir == DIRN_DOWN && current_floor != 0) {
		printf("Kris sa print, og print ble det\n");
		qs_get_below_order();
		return;
	} else if(current_dir == 0 && last_dir == DIRN_UP && current_floor == 3) {
		qs_get_below_order();
		return;
	} else if(current_dir == 0 && last_dir == DIRN_DOWN && current_floor == 0) {
		qs_get_above_order();
		return;
	}

}

int qs_get_number_of_orders() {
	int sum = 0;
	for (int floor = 0; floor < 4; floor++) {
		for(int button = 0; button < 3; button++) {
			sum += order_table[button][floor];
		}
	}
	return sum;
}

void qs_set_next_floor(int floor) {
	assert(floor>=0);
	next_floor = floor;
}

int qs_get_next_floor() {
	assert(next_floor>=0);
	return next_floor;
}

void qs_set_current_floor(int floor) {
	current_floor = floor;
}

int qs_get_current_floor() {
	return current_floor;
}

void print_next_floor() {
	printf("next floor: %d\n",next_floor);
}

void print_current_floor() {
	printf("current floor: %d\n",current_floor);
}
void print_matrix(){

	for(int floor = 0; floor < 4; floor++) {									
		for (int button = 0; button < 3; button++) {

			printf("%d, ", order_table[button][floor]);

				if (button == 2){

					printf("\n");
				}
		}
	}
}

void qs_set_current_dir(int direction){
	current_dir = direction;
}


int qs_get_current_dir() {
	return current_dir;
}

int qs_get_last_dir() {
	return last_dir;
}

void qs_set_last_dir(int direction) {
	last_dir = direction;
}
