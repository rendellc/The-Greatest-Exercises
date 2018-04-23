#include "DoorController.h"
#include "FloorDetector.h"
#include "Timer.h"
#include "ElevatorFSM.h"
#include "FIFO_Queue.h"
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>



/// --- Structs and typedefs ---
typedef enum { 
    state_invalid, 
    state_initialize, 
    state_standby, 
    state_moving_up,
    state_moving_down, 
    state_arrived, 
    state_stop 
} EL_state_t;

/// --- Constants ---
static const int DOOR_OPEN_TIME = 3000; // milliseconds
static const int STOP_TIME = 3000; // milliseconds


/// --- Variables ---
static EL_state_t state = state_initialize;
static int doorTimerStarted = false; // 0 if unstarted, 1 if started
static int moveDirection = 0; // -1 down and 1 is up, 0 is no direction

static Node* EL_queue = NULL;

static int commandLights[N_FLOORS] = {false}; // "boolean" array 
static int callUpLights[N_FLOORS] = {false}; // "boolean" array
static int callDownLights[N_FLOORS] = {false}; // "boolean" array



void EL_initialize(){
    if (!FD_isOnFloor())
        HW_setMotorDirection(DIRN_DOWN);
    
    while (!FD_isOnFloor()); //loops until elevator hits (any) floor


    HW_setMotorDirection(DIRN_STOP);
    DC_closeDoor();
    
    printf("Elevator init complete.\n");
    state = state_standby;
}


bool EL_checkAndUpdateOrders(){
    int newUpdates = false;

    for (int f = 0; f < N_FLOORS; ++f){
        if (HW_getButtonSignal(BUTTON_COMMAND, f)){
            FIFO_addFloor(&EL_commandQueue, f, BUTTON_COMMAND);
            newUpdates = true;
        }
    }
    
    for (int f = 0; f < N_FLOORS - 1; ++f){
        if (HW_getButtonSignal(BUTTON_CALL_UP, f)){
            FIFO_addFloor(&EL_callUpQueue, f, BUTTON_CALL_UP);
            newUpdates = true;
        }
    }

    for (int f = 1; f < N_FLOORS; ++f){
        if (HW_getButtonSignal(BUTTON_CALL_DOWN, f)){
            FIFO_addFloor(&EL_callDownQueue, f, BUTTON_CALL_DOWN);
            newUpdates = true;
        }
    }
    
    return newUpdates;
}

void EL_updateFloorIndicators(){
    int currentFloor = HW_getFloorSensorSignal();

    if (currentFloor != -1){
        HW_setFloorIndicator(currentFloor);
    }    
}


void EL_updateQueueLights(){

    // --- find out which lights to update ---
    for (int f = 0; f < N_FLOORS; ++f){
        if (commandLights[f] != FIFO_floorInQueue(&EL_queue, f, BUTTON_COMMAND)){ // if not correct, then
            commandLights[f] = !commandLights[f]; // toggle light
        }
        if (callUpLights[f] != FIFO_floorInQueue(&EL_queue, f, BUTTON_CALL_UP)){
            callUpLights[f] = !callUpLights[f]; // toggle light
        }
        if (callDownLights[f] != FIFO_floorInQueue(&EL_queue, f, BUTTON_CALL_DOWN)){
            callDownLights[f] = !callDownLights[f]; // toggle light
        }
    }


    // --- update the lights ---
    for (int f = 0; f < N_FLOORS; ++f){
        HW_setButtonLamp(BUTTON_COMMAND, f, commandLights[f]);
        
    }
    for (int f = 0; f < N_FLOORS - 1; ++f){
        HW_setButtonLamp(BUTTON_CALL_UP, f, callUpLights[f]);
    }
    for (int f = 1; f < N_FLOORS; ++f){
        HW_setButtonLamp(BUTTON_CALL_DOWN, f, callDownLights[f]);
    }
}
 

inline int EL_getNextFloor(){
    return FIFO_getTopPriority(&EL_queue);
}

void EL_gotoFloor(int wantedFloor){
    assert(wantedFloor < N_FLOORS);
    assert(wantedFloor >= -1);
    

    int currentFloor = FD_getFloor();

    if (currentFloor == -1){
        return;  // dont do anything
    }

    // accounts for emergency stops between floors
    bool floorCheck = (double)wantedFloor >= ((double)currentFloor + 0.5*(double)moveDirection); 

    if (floorCheck){
        state = state_moving_up;
    } else {
        state = state_moving_down;
    } 
}

void EL_mainloop(void){

    int nextFloor = -1;
    bool orderUpdateCheck = false;
    int topPriorityFloor = -1;


    while (true){
        EL_updateFloorIndicators();
        EL_updateQueueLights();


        switch (state){
            case state_initialize:
                EL_initialize();
                break;

            case state_standby:
                if (HW_getStopSignal()){
                    state = state_stop;
                    break;
                }


                if (EL_checkAndUpdateOrders()){
                    EL_updateQueueLights();
                }


                if (!FIFO_isEmpty(&EL_queue, BUTTON_COMMAND) 
                    || !FIFO_isEmpty(&EL_queue, BUTTON_CALL_UP) 
                    || !FIFO_isEmpty(&EL_queue, BUTTON_CALL_DOWN))
                {
                    nextFloor = EL_getNextFloor();
                    EL_gotoFloor(nextFloor);
                }

                break;

            case state_moving_up:
                if (HW_getStopSignal()){
                    state = state_stop;
                    break;
                }

                HW_setMotorDirection(DIRN_UP);
                moveDirection = DIRN_UP;

                if (EL_checkAndUpdateOrders()){
                    EL_updateQueueLights();
                }

                if (FD_isOnFloor()){

                    int currentFloor = FD_getFloor();
                    // check command and up queue
                    if (FIFO_floorInQueue(&EL_queue, currentFloor, BUTTON_COMMAND) 
                        || FIFO_floorInQueue(&EL_queue, currentFloor, BUTTON_CALL_UP))
                    {
                        // should stop here
                        FIFO_popFloor(&EL_queue, currentFloor, BUTTON_COMMAND);
                        FIFO_popFloor(&EL_queue, currentFloor, BUTTON_CALL_UP);
                        state = state_arrived;
                    }

                    // check down queue if others are empty
                    if (FIFO_isEmpty(&EL_queue, BUTTON_CALL_UP) 
                        && FIFO_isEmpty(&EL_queue, BUTTON_COMMAND) 
                        && FIFO_floorInQueue(&EL_queue, currentFloor, BUTTON_CALL_DOWN))
                    {
                        FIFO_popFloor(&EL_queue, currentFloor, BUTTON_CALL_DOWN);
                        state = state_arrived;
                    }
                }

                break;

            case state_moving_down:
                if (HW_getStopSignal()){
                    state = state_stop;
                    break;
                }

                HW_setMotorDirection(DIRN_DOWN);
                moveDirection = DIRN_DOWN;

                if (EL_checkAndUpdateOrders()){
                    EL_updateQueueLights();
                }

                if (FD_isOnFloor()){

                    int currentFloor = FD_getFloor();
                    // check command and up queue
                    if (FIFO_floorInQueue(&EL_queue, currentFloor, BUTTON_COMMAND) 
                        || FIFO_floorInQueue(&EL_queue, currentFloor, BUTTON_CALL_DOWN))
                    {
                        // should stop here
                        FIFO_popFloor(&EL_queue, currentFloor, BUTTON_COMMAND);
                        FIFO_popFloor(&EL_queue, currentFloor, BUTTON_CALL_DOWN);
                        state = state_arrived;
                    }

                    // check down queue if others are empty
                    if (FIFO_isEmpty(&EL_queue, BUTTON_CALL_DOWN) 
                        && FIFO_isEmpty(&EL_queue, BUTTON_COMMAND) 
                        && FIFO_floorInQueue(&EL_queue, currentFloor, BUTTON_CALL_UP))
                    {
                        FIFO_popFloor(&EL_queue, currentFloor, BUTTON_CALL_UP);
                        state = state_arrived;
                    }
                }
                break;

            case state_stop:
                HW_setMotorDirection(DIRN_STOP);
                TIMER_set(STOP_TIME);
                FIFO_deleteAll(&EL_queue);
                EL_updateQueueLights();

                if (FD_isOnFloor())
                    DC_openDoor();

                TIMER_start();
                while (!TIMER_timeout()){ // loop until timeout
                    if (HW_getStopSignal()){
                        HW_setStopLamp(1);
                        TIMER_start(); // start timer from scratch
                    } else{
                        HW_setStopLamp(0);
                    }
                }


                DC_closeDoor();
                state = state_standby;
                break;

            case state_arrived:
                if (HW_getStopSignal()){
                    state = state_stop;
                    break;
                }

                // assumes correct floor
                HW_setMotorDirection(DIRN_STOP);
                moveDirection = DIRN_STOP;
                EL_updateQueueLights();
                EL_checkAndUpdateOrders();
                
                if (!doorTimerStarted){
                    TIMER_set(DOOR_OPEN_TIME);
                    TIMER_start();
                    DC_openDoor();
                    doorTimerStarted = 1;
                }

                if (TIMER_timeout()){
                    doorTimerStarted = 0;
                    DC_closeDoor();
                    state = state_standby;
                }

                break;
            default:
                // should not happen
                printf("ERROR: state %d not covered by switch cases", state);
        }
    }
}