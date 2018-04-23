#include "elev.h"
#include "executive.h"
#include <stdio.h>
#include <sys/time.h>
#include "buttonspressed.h"


double set_timer(void){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}

int compare_timer(double comparedTime){ //Returnerer 1 hvis det har gått 3s siden comparedTime, 0 hvis ikke.
	double currentTime = set_timer();
	if ((currentTime-comparedTime) > 3){
		return 1;
	}
	return 0;
}

void set_light(void){ //Itererer gjennom buttonsPressed og setter på lysene.
	elev_button_type_t buttonType = BUTTON_CALL_UP;
	int floor = 0;
	for (int i = 0; i < 12; i++){
		if((i == 3) || (i == 4)){
		continue;}
		from_index_to_button_and_floor(i,&buttonType,&floor);
		elev_set_button_lamp(buttonType, floor, get_button_pressed(i));
	}
	return;
}

void from_index_to_button_and_floor(int index, elev_button_type_t *buttonType, int *floor){ //Brukes til å finne hvilken type knapp/etasje som befinner seg på en bestemt index i buttonsPressed
	if (index < 4){
		*buttonType = BUTTON_CALL_UP;
		*floor = index; 
		return; 
	}
	else if (index < 8){
		*buttonType = BUTTON_CALL_DOWN;
		*floor = index - 4;
		return;
	}
	else{
		*buttonType = BUTTON_COMMAND;
		*floor = index - 8;
		return;
	}
}

void set_floor_lamp(void){ //Setter etasjelysene
	int floor = elev_get_floor_sensor_signal();
	if (floor == -1){
		return;}
	elev_set_floor_indicator(floor);
	return;
}

void destination_reached(void){ //Kalles når stop_or_not() har bestemt at man skal stoppe heisen. Stopper heisen, skrur av bestillingslys og åpner dør.
	elev_set_motor_direction(0);
	int floor = elev_get_floor_sensor_signal();
	reset_button_pressed(floor);
	reset_button_pressed(floor+4);
	reset_button_pressed(floor+8);
	set_light();
	doorOpen = 1;
	elev_set_door_open_lamp(1);
	return;
}

void stop(void){ //Poller stoppknappen og bestemmer om man har stoppet mellom etasjer eller i en etasje.
	if((elev_get_stop_signal() == 0) && (stopButtonPressed == -1) && (sum_of_buttons_pressed() == 0)) { //Dette er casen der stoppknappen er trykket mellom to etasjer, men sluppet igjen, og det ikke er noen bestillinger inne.
		return;
	}
	else if (elev_get_stop_signal() == 0){
		stopButtonPressed = 0;
		return;
	}
	// Funksjonen går videre når knappen er trykket
	else if(elev_get_floor_sensor_signal() > -1){
		elev_set_door_open_lamp(1);
	}
	while (elev_get_stop_signal() == 1){ //Dette skjer så lenge knappen holdes inne.
		elev_set_motor_direction(0);
		stopButtonPressed = 1;
		elev_set_stop_lamp(1);
		clear_orders();
		set_light();
	}
	elev_set_stop_lamp(0);

	if(elev_get_floor_sensor_signal() > -1){ //Hvis man er i en etasje, holdes døren åpen i 3s, før noe kan skje videre.
		double timer_start = set_timer();
		while (compare_timer(timer_start) != 1){
			continue;
		}
		elev_set_door_open_lamp(0);
	}
	else if(elev_get_floor_sensor_signal() == -1){ //Er man mellom to etasjer, settes stopButtonPressed = 1
		stopButtonPressed = -1;
	}
	elev_set_motor_direction(0);
	return;
}

void initialize(void){ //Initialiserer heisen hvis den er mellom to etasjer til å begynne med.
	while (elev_get_floor_sensor_signal() == -1){
		elev_set_motor_direction(-1);
	}
	elev_set_motor_direction(0);
}

int order_over(void){ //Sjekker om det finnes ordre over den etasjen man befinner seg i. Hvis stoppknappen er trykket mellom to etasjer, tar denne funksjonen seg av å bestemme heisens posisjon.
	int currentFloor = elev_get_floor_sensor_signal();

	if (stopButtonPressed == -1){  //Her endres currentFloor hvis heisen står i ro mellom to etasjer.
		if(currentDir == 1){
			currentFloor = lastFloor;
		}
		else if(currentDir == -1){
			currentFloor = lastFloor-1;
		}
	}
	
	if(currentFloor == -1){
		return 2;
	}
	for (elev_button_type_t button = BUTTON_CALL_UP; button < 3; button++){ //Itererer gjennom buttonsPressed fra currentFloor og opp, og leter etter bestillinger. 
		for (int floor = currentFloor+1; floor < 4; floor++){
			if(get_button_pressed(4*button+floor) == 1){
				return 1;
			}
		} 
	}
return 0;
}

int order_under(void){ //Samme som order_over() bare at den sjekker om det finnes ordre under. 
	int currentFloor = elev_get_floor_sensor_signal();
	if (stopButtonPressed == -1){
		if(currentDir == 1){
			currentFloor = lastFloor+1;
		}
		else if(currentDir == -1){
			currentFloor = lastFloor;
		}
	}
	
	if(currentFloor == -1){
		return 2;
	}
	for (elev_button_type_t button = BUTTON_CALL_UP; button < 3; button++){
		for (int floor = currentFloor-1; floor > -1; floor--){
			if(get_button_pressed(4*button+floor) == 1){
				return 1;
			}
		} 
	}
	return 0;
}


int stop_or_not(void){ //Bestemmer om heisen skal stoppe i den etasjen heisen befinner seg i. Kaller da på destination_reached().
	int currentFloor = elev_get_floor_sensor_signal();
	if(currentFloor == -1){
		return 0;
	}
	
	if((get_button_pressed(currentFloor) == 0) && (get_button_pressed(currentFloor+4) == 0) && (get_button_pressed(currentFloor+8) == 0)){
		return 0;
	}
	elev_button_type_t buttonType1 = get_button_pressed(currentFloor); //Bestillingsknapp opp
	elev_button_type_t buttonType2 = get_button_pressed(currentFloor+4); //Bestillingsknapp ned
	elev_button_type_t buttonType3 = get_button_pressed(currentFloor+8); //Bestillingsknapp etasje

	if((buttonType1+buttonType2+buttonType3 > 0) && (doorOpen == 1)){ //Hvis heisen allerede har stoppet i en etasje og får en ny bestilling fra/til samme etasje vil destination_reached() kalles.
		destination_reached();
		return 1;
	}
	if(buttonType3 == 1){ //Heisen stopper hvis etasjen er trykket på heispanelet. 
		destination_reached();
		return 1;
	}
	if((currentDir == buttonType1) || ((currentDir == 1) && (order_over() == 0))){ //Hvis currentDir == 1(opp) og en oppknapp er trykket i currentFloor, skal heisen stoppe.
		return 1;																   //Den skal også stoppe hvis det ikke er noen bestillinger over, uavhengig av hvilken knapp som er trykket.
		destination_reached();
	}
	if((currentDir+2 == buttonType2) || ((currentDir == -1) && (order_under() == 0))){ //Hvis currentDir == -1(ned) og en nedknapp er trykket i currentFloor, skal heisen stoppe.
		destination_reached(); 														   //Den skal også stoppe uansett hvis det ikke er noen bestillinger under currentFloor.
		return 1;
	}
	if((currentDir == 0) && ((buttonType1 == 1) || (buttonType2 == 1))){ //Hvis heisen har ekspedert alle bestillinger og nå står i ro i en etasje, men får en bestilling i den etasjen man står i, skal destination_reached() kalles.
		destination_reached();
		return 1;
	}

	return 0;

}



void set_direction(void){ //Bestemmer retningen på heisen basert på om det er ordre over eller under heisen.
	if((order_under() == 0) && (order_over() == 0) && (stopButtonPressed > -1)){ //Hvis heisen ikke har bestillinger inne, og den står i en etasje (stopButtonPressed == -1 betyr at den har stoppet mellom to etasjer). Skal currentDir = 0;
		currentDir = 0;
	}
	else if((order_over() == 1) && (order_under() == 0)){ //Heisen kjører oppover hvis den har bestillinger over
		currentDir = 1;
	}
	else if ((order_under() == 1) && (order_over() == 0)){ //Heisen kjører nedover hvis den har bestillinger under.
		currentDir = -1;
	}
	else if(((stopButtonPressed == 1) || (stopButtonPressed == -1)) && (order_over() == 1) && (order_under() == 1)){ //Hvis tilfellet er at en stoppknapp har blitt trykket inn, og heisen får to bestillinger nøyaktig samtidig, 
		currentDir = 1;																								 //vil den velge retning opp.	
	}
	else if((currentDir == 0) && (order_over() == 1) && (order_under() == 1)){ //Samme som tilfellet over, blir to ordre plassert nøyaktig samtidig, vil heisen ekspedere ordre over currentFloor først.
		currentDir = 1;
	}
	else{return;}
}

void last_floor(void){ // Lagrer den siste passerte etasjen i lastFloor
	static int currentFloor = 0;
	if(elev_get_floor_sensor_signal() == -1){
		lastFloor = currentFloor;
	}
	else{
		currentFloor = elev_get_floor_sensor_signal();
		lastFloor = currentFloor;

	}

}

void set_motor_direction(void){  //Setter motoren i den retningen som blir bestemt av set_direction().
	if((stopButtonPressed == -1) && (sum_of_buttons_pressed() == 0)){
		elev_set_motor_direction(0);
		return;	
	}
	elev_set_motor_direction(currentDir);
	return;
}
