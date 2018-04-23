#include "elev.h"
#include <stdio.h>
#include "statemachine.h"
#include "timer.h"



int main(){
	
	int LastStopButton = 0;
	int LastFloorSensorSignal = -1;

	// Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    
    elev_set_motor_direction(DIRN_UP);	
    
	while (elev_get_floor_sensor_signal() == -1){	 
    }

    int floor = elev_get_floor_sensor_signal();
    elev_set_motor_direction(0);
    elev_set_floor_indicator(floor);

   

    //Turn of all lights 
    for(int floor=0; floor<N_FLOORS-1 ;floor++){
        elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
    }
    for(int floor=1; floor<N_FLOORS ;floor++){
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);   
    }
    for(int floor=0; floor<N_FLOORS ;floor++){
        elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
    }


    


    while (1) {

    	sm_check_idle();

        int FloorSensorSignal = elev_get_floor_sensor_signal();

        if(LastFloorSensorSignal != FloorSensorSignal){
            elev_set_floor_indicator(FloorSensorSignal);
            sm_arrived_at_floor(FloorSensorSignal);

        }


    	int StopButton = elev_get_stop_signal();
    	if(LastStopButton != StopButton){
    		if(StopButton==1){
    			sm_stop_button_pressed();
    		}
    		else{
    			sm_stop_button_released();
    		}

    		LastStopButton = StopButton;
    	}

 		
	
    
        if(timer_end() == 1){
        	sm_timeout();
        }

        //Checks button signal 
        for(int floor = 0; floor < N_FLOORS-1 ; floor++){ 
            if(elev_get_button_signal(BUTTON_CALL_UP, floor)){
                sm_add_order(BUTTON_CALL_UP,floor);
            }
        }
        for(int floor = 1; floor < N_FLOORS ;floor++){
            if(elev_get_button_signal(BUTTON_CALL_DOWN, floor)){
                sm_add_order(BUTTON_CALL_DOWN,floor);
            }
        }
        for(int floor = 0; floor < N_FLOORS ;floor++){
            if(elev_get_button_signal(BUTTON_COMMAND, floor)){
                sm_add_order(BUTTON_COMMAND,floor);
            }
        }
        

     } 
    
    return 0;

}
