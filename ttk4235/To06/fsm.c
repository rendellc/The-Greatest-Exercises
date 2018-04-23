
//Moduler/klasser fra heisdriveren

#include "fsm.h"
#include "io.h"
#include "elev.h"
#include "channels.h"

//Egenimplementerte moduler

#include "timer.h"
#include "qs.h"

//Andre bibleotek

#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>



//Denne tilstanden setter heisen i bevegelse, og behandler bestillinger under kjøretiden

int fsm_drive_elevator() {

	elev_set_door_open_lamp(0);
	qs_set_priority(); 


	if (qs_get_next_floor() - qs_get_current_floor() > 0) { //Setter motor-retning opp dersom neste etasje er over nåværende
		elev_set_motor_direction(DIRN_UP);
		qs_set_current_dir(DIRN_UP);

	} else if(qs_get_next_floor() - qs_get_current_floor() < 0) { //Setter motor-retning ned dersom neste etasje er under nåværende		
		elev_set_motor_direction(DIRN_DOWN);
		qs_set_current_dir(DIRN_DOWN);

	} else { //Stopper motor eller (Dvs om neste skulle være i nåværende)
		elev_set_motor_direction(0);
		qs_set_current_dir(0);
		return 0;
	}

	while(elev_get_floor_sensor_signal() != qs_get_next_floor()) { //Denne løkken kjører så lenge den ikke er i riktig etasje

		if(elev_get_stop_signal()) { //Bryter ut av tilstanden dersom stopp-knappen trykkes
			return 0;
		}

		int floor_sensor = elev_get_floor_sensor_signal();	//Oppdaterer etasje-indikatorene dersom heisen kjører forbi en etasje
		if(floor_sensor != -1) {
			elev_set_floor_indicator(floor_sensor);
			qs_set_current_floor(floor_sensor);
			
		} 
		qs_check_orders(); //Sjekker bestillinger samtidig som heisen kjører
		qs_set_priority();
		
	}


	//Her har heisen hankommet riktig etasje, og vil dermed stoppe heisen, og bryte ut av tilstanden
	qs_set_current_floor(elev_get_floor_sensor_signal());
	qs_set_last_dir(qs_get_current_dir());
	elev_set_motor_direction(0);
	print_current_floor();

	return 0;
}


void fsm_arrived_floor() {

	printf("Entered arrive: \n");
	elev_set_floor_indicator(qs_get_current_floor());

	qs_set_current_dir(0); //Heisen står stille og setter nåværende retning til null

	
	qs_delete_orders(); //Sletter alle ordre i etasjen heisen har stoppet i
	
	//Starter timer-sekvensen når døren åpnes

	elev_set_door_open_lamp(1);
	
	t_start_timer();
	while (!t_wait_3_sec()) { //Bryter ut av løkken etter at timeren har registrer at det har gått 3 sekunder
		//printf("hei\n" );
		if(elev_get_stop_signal()){ //Går ut av tilstanden hvis stopp-knappen trykkes

			return;
		}
		qs_check_orders();
		qs_delete_orders();
	}
	
	elev_set_door_open_lamp(0);

	//Avslutter timer-sekvensen og døren lukkes

	while(qs_get_number_of_orders() == 0) { //Så lenge det ikke finnes ordre vil heisen 'polle' etter bestillinger i denne løkken


		//Bryter ut av løkken kun om stopp-knappen trykkes eller om det skjer en bestilling

		if(elev_get_stop_signal()){
			return;
		}

		if (qs_check_orders()){
			break;
		}
	}
	qs_set_priority();

}

void fsm_stop_elevator(){

	//Restarter heisen og sletter alle ordre

	int last_dir = qs_get_current_dir();
	qs_set_current_dir(0);
	qs_set_next_floor(qs_get_current_floor());
	elev_set_motor_direction(0);
	elev_set_stop_lamp(1);
	qs_reset_orders();

	print_matrix();

	if (elev_get_floor_sensor_signal() != -1){ //Dersom heisen befinner seg i en etasje vil den gå til arrived_floor-tilstanden etter at stopp-knappen er sluppet
		while(elev_get_stop_signal()){

			continue;
		}
		elev_set_stop_lamp(0);
		return;

	} else { //Går inn i else-betingelsen dersom heisen befinner seg mellom to etasjer
		while(elev_get_stop_signal()) {
			continue;
		}
		elev_set_stop_lamp(0);

		while(!qs_check_orders()) { //Vil bryte ut av løkken dersom det skjer en bestilling
			if (elev_get_stop_signal())
			{
				elev_set_stop_lamp(1);
				while(elev_get_stop_signal()) { //Gjør det mulig å trykke/holde inne stopp-knappen selv når den 'poller' på bestilling i udefinert tilstand
					continue;
				}
				elev_set_stop_lamp(0);
			}
			continue;
		}

		//Følgende algoritme avgjør om heisen skal opp eller ned hvis heisen bestilles til samme etasje som etasje-indikatoren tilsier. Bruker da forrige retning til å bestemme om den skal opp eller ned
		
		if (qs_get_next_floor() == qs_get_current_floor())
		{
			if(last_dir == DIRN_UP){
				if (qs_get_current_floor() != 3){
					qs_set_current_floor(qs_get_current_floor() + 1);
				}
			}
			else if (last_dir == DIRN_DOWN)
			{
				if(qs_get_current_floor() != 0) {
					qs_set_current_floor(qs_get_current_floor() - 1);
				}
			}		
		}
		
	}
	
}