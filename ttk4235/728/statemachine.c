//
//  statemachine.c
//  HeisprosjektTest
//
//  Created by Andrea Holten on 12.03.2017.
//  Copyright © 2017 Andrea Holten. All rights reserved.
//

#include "statemachine.h"
#include "elev.h"
#include <stdio.h>
#include "placeorder.h"
#include "timer.h"


typedef enum{
    S_IDLE,
    S_Move,
    S_StopButtonAtFloor,
    S_StopButtonBetweenFloor,
   	S_OpenDoor,
}FSMstate;


static int current_floor; //0,1,2,3
static int between_floors = 0;
static elev_motor_direction_t direction = DIRN_UP;     //Down = -1, Stop = 0, Up = 1



FSMstate state = S_IDLE;

void open_door(void){

    state = S_OpenDoor;
    elev_set_motor_direction(DIRN_STOP);
    elev_set_door_open_lamp(1);
    timer_start();
    
}


void sm_stop_button_pressed(void){
    elev_set_stop_lamp(1);
    
    int floor = elev_get_floor_sensor_signal();
    elev_set_motor_direction(DIRN_STOP);
    
    po_delete_all_orders();
    
    //All buttonlights off
    for(int floor=0; floor<N_FLOORS-1 ;floor++){
        elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
    }
    for(int floor=1; floor<N_FLOORS ;floor++){
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
    }
    for(int floor=0; floor<N_FLOORS ;floor++){
        elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
    }
    
    if(floor != -1){
        state = S_StopButtonAtFloor;
        elev_set_door_open_lamp(1);
    }
    
    else{
        state = S_StopButtonBetweenFloor;
        between_floors = 1;
        
    }
}


void sm_stop_button_released(void){
    
    switch(state){
        case S_StopButtonAtFloor:
            open_door();
            state = S_IDLE;
            break;
        case S_StopButtonBetweenFloor:
            state = S_IDLE;
            break;
        default: break;
    }
    
    elev_set_stop_lamp(0);
}




void sm_arrived_at_floor(int floor){
    
    current_floor = floor;
    
    
    // Check order at floor

    // Button command
    if(po_check_order(floor + 6)){
        elev_set_button_lamp(BUTTON_COMMAND,floor,0);
        po_delete_order(floor+6);
        open_door();
        
    }
    
    
    //Button up if direction up
    if( (po_check_order(floor)) && (floor != 3) && (direction == DIRN_UP) ){
        if(po_check_order(floor +2)){
            elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
            po_delete_order(floor+2);
        }
        elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
        po_delete_order(floor);
        open_door();
    }
    
    //Button down if direction down
    if((po_check_order(floor + 2)) && (floor != 0)  && (direction == DIRN_DOWN)){
        if(po_check_order(floor)){
            elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
            po_delete_order(floor);
        }
        elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
        po_delete_order(floor+2);
        open_door();
        
    }
    
    //Check if the elevator should contuinue in same direction, or stop
    if (state != S_OpenDoor){
        if(direction == DIRN_UP){
            if(sm_requests_above() == 1){
                return;
            }
            else if(po_check_order(floor+2) == 1){
                direction = DIRN_STOP;
                elev_set_button_lamp(BUTTON_CALL_DOWN,floor,0);
                po_delete_order(floor+2);
                open_door();
            }
                
        }
        
        if(direction == DIRN_DOWN){
            if(sm_requests_below() == 1){
                return;
            }
            else if(po_check_order(floor) == 1){
                direction = DIRN_STOP;
                elev_set_button_lamp(BUTTON_CALL_UP,floor,0);
                po_delete_order(floor);
                open_door();
            }
            
        }

    }
    
    
   
    
}



//Add order to queue - set light if add_order == TRUE
void sm_add_order(elev_button_type_t button, int floor){
    
    if( state == S_IDLE || state == S_Move || state == S_OpenDoor){
        if (po_add_order(button, floor) == 1){
            elev_set_button_lamp(button, floor, 1);
        }
    }
}

void sm_timeout(void){
    elev_set_door_open_lamp(0);
    
    //find new order 
    if(sm_set_direction()){
        elev_set_motor_direction(direction);
        state = S_Move;
    }
    else{
        state = S_IDLE;
    }
        
}


void sm_check_idle(void){
    if (state == S_IDLE){
        if(sm_set_direction()){
            elev_set_motor_direction(direction);
            state = S_Move;
        }      
    }   
}


int sm_set_direction(void){
    
    switch(direction){
        case DIRN_UP:
            
            if(between_floors == 1){
                if((po_check_order(current_floor) == 1) || (po_check_order(current_floor+2) == 1) || (po_check_order(current_floor+6) == 1)){
                    direction = DIRN_DOWN;
                    between_floors = 0;
                    return 1;
                }
                
            }
            
            if (sm_check_if_stop()){
                direction = DIRN_STOP;
                return 1;
            }

            if(sm_requests_above() == 1){
                if(between_floors == 1){
                    between_floors = 0;
                }
                return 1;
            }


            else if(sm_requests_below()){
                direction = DIRN_DOWN;
                if(between_floors == 1){
                    between_floors = 0;
                }
                return 1;
            }
            else{
                return 0;
            }
            

        case DIRN_DOWN:
        case DIRN_STOP:
            if(between_floors == 1){
                if((po_check_order(current_floor) == 1) || (po_check_order(current_floor+2) == 1) || (po_check_order(current_floor+6) == 1)){
                    direction = DIRN_UP;
                    between_floors = 0;
                    return 1;
                }
                
            }

            if (sm_check_if_stop()){
                direction = DIRN_STOP;
                return 1;
            }
            
            if(sm_requests_below()){
                direction = DIRN_DOWN;
                if(between_floors == 1){
                    between_floors = 0;
                }
                return 1;
                
            }
            
            else if(sm_requests_above()){
                direction = DIRN_UP;
                if(between_floors == 1){
                    between_floors = 0;
                }
                return 1;
            }
            else{
                return 0;
            }
        default:
            direction = DIRN_STOP;
            return 0;
                
    }

}
    


int sm_requests_above(void){
    
    for (int floor = current_floor +1 ; floor <= N_FLOORS-2 ; floor++){
        if((po_check_order(floor) == 1 )){
            return 1;
        }
    }
    for (int floor = N_FLOORS -1 ; floor > current_floor ; floor--){
        if((po_check_order(floor+2)==1) || (po_check_order(floor + 6)==1)){
            return 1;
        }
    }
    return 0;
}


int sm_requests_below(void){
    
    for (int floor = current_floor-1 ; floor > 0 ; floor--){
        if((po_check_order(floor + 2) == 1 )){
            return 1;
        }
    }
    for (int floor = 0 ; floor < current_floor ; floor++){
        if((po_check_order(floor)==1) || (po_check_order(floor + 6) == 1 )){
            return 1;
        }
    }
    return 0;

}

//Check if order on current_floor
int sm_check_if_stop(void){
    int stop = 0;


    if(po_check_order(current_floor + 6)){
        elev_set_button_lamp(BUTTON_COMMAND,current_floor,0);
        po_delete_order(current_floor+6);
        stop = 1;  
    }
    
    if(po_check_order(current_floor)&& (current_floor != 3)){
        elev_set_button_lamp(BUTTON_CALL_UP,current_floor,0);
        po_delete_order(current_floor);
        stop = 1;
    }
    
    
    if(po_check_order(current_floor + 2) && (current_floor!=0)){ 
        elev_set_button_lamp(BUTTON_CALL_DOWN,current_floor,0);
        po_delete_order(current_floor+2);
        stop = 1;
        
    }

    if(stop == 1){
        open_door();
        return 1;
    }
    
    return 0;
    
}








