#include "LightController.h"
#include "DoorController.h"
#include "FloorDetector.h"
#include "Timer.h"
//#include "Elevator.h"
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

static Node* EL_commandQueue   = NULL;
static Node* EL_callUpQueue    = NULL;
static Node* EL_callDownQueue  = NULL;

static int commandLights[N_FLOORS] = {false}; // "boolean" array 
static int callUpLights[N_FLOORS] = {false}; // "boolean" array
static int callDownLights[N_FLOORS] = {false}; // "boolean" array



void EL_initialize(){
    DC_openDoor();
    if (!FD_isOnFloor())
        HW_setMotorDirection(DIRN_DOWN);
    
    while (!FD_isOnFloor()); //loops until elevator hits (any) floor


    HW_setMotorDirection(DIRN_STOP);
    DC_closeDoor();
    
    printf("Elevator init complete.\n");
    state = state_standby;
}


bool EL_checkAndUpdateOrders(void){
    int newUpdates = false;

    for (int f = 0; f < N_FLOORS; ++f){
        if (HW_getButtonSignal(BUTTON_COMMAND, f)){
            FIFO_addFloor(&EL_commandQueue, f);
            newUpdates = true;
        }
    }
    for (int f = 0; f < N_FLOORS - 1; ++f){
        if (HW_getButtonSignal(BUTTON_CALL_UP, f)){
            FIFO_addFloor(&EL_callUpQueue, f);
            newUpdates = true;
        }
    }
    for (int f = 1; f < N_FLOORS; ++f){
        if (HW_getButtonSignal(BUTTON_CALL_DOWN, f)){
            FIFO_addFloor(&EL_callDownQueue, f);
            newUpdates = true;
        }
    }
    
    return newUpdates;
}

void EL_updateQueueLights(){

    // --- find out what lights to update
    for (int f = 0; f < N_FLOORS; ++f){
        if (commandLights[f] != FIFO_floorInQueue(&EL_commandQueue, f)){ // if not correct, then
            commandLights[f] = !commandLights[f]; // toggle light
        }
        if (callUpLights[f] != FIFO_floorInQueue(&EL_callUpQueue, f)){
            callUpLights[f] = !callUpLights[f]; // toggle light
        }
        if (callDownLights[f] != FIFO_floorInQueue(&EL_callDownQueue, f)){
            callDownLights[f] = !callDownLights[f]; // toggle light
        }
    }


    // --- update the lights
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


void EL_stop(){
    HW_setMotorDirection(DIRN_STOP);
    HW_setStopLamp(1);
    TIMER_set(STOP_TIME);
    FIFO_deleteAll(&EL_commandQueue);
    FIFO_deleteAll(&EL_callUpQueue);
    FIFO_deleteAll(&EL_callDownQueue);
    EL_updateQueueLights();

    if (FD_isOnFloor())
        DC_openDoor();

    TIMER_start();

    while (!TIMER_timeout()){ // loop until timeout
        if (HW_getStopSignal()){
            TIMER_start(); // start timer from scratch
        }
    }

    HW_setStopLamp(0);
    DC_closeDoor();
    state = state_standby;
}

int EL_getNextFloor(){

    int nextFloor = FIFO_getTopPriority(&EL_commandQueue);
    printf("nextFloor = %d\n", nextFloor);
    if (nextFloor != -1){
        return nextFloor;
    }
    nextFloor = FIFO_getTopPriority(&EL_callUpQueue);
    printf("nextFloor = %d\n", nextFloor);
    if (nextFloor != -1){
        return nextFloor;
    }
    nextFloor = FIFO_getTopPriority(&EL_callDownQueue);
    printf("nextFloor = %d\n", nextFloor);
    if (nextFloor != -1){
        return nextFloor;
    }



    return -1;
}

void EL_gotoFloor(int wantedFloor){
    assert(wantedFloor < N_FLOORS);
    assert(wantedFloor >= -1);
    

    int currentFloor = FD_getFloor();
    printf("currentFloor = %d\n", currentFloor);

    if (currentFloor == -1){
        return;  // dont do anything
    }


    if (wantedFloor > currentFloor){
        printf("state_moving_up\n");
        state = state_moving_up;
    } else if (wantedFloor < currentFloor) {
        printf("state_moving_down\n");
        state = state_moving_down;
    } else {
        printf("state_standby\n");
        state = state_arrived;
    }
}

void EL_mainloop(void){

    int nextFloor = -1;
    bool orderUpdateCheck = false;
    int topPriorityFloor = -1;


    while (true){
        LC_updateFloorIndicators();


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


                if (!FIFO_isEmpty(&EL_commandQueue) || !FIFO_isEmpty(&EL_callUpQueue) || !FIFO_isEmpty(&EL_callDownQueue)){
                    printf("Some queues are not empty, keep going\n");
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

                if (EL_checkAndUpdateOrders()){
                    printf("Orders were added\n");
                    EL_updateQueueLights();
                }

                if (FD_isOnFloor()){

                    int currentFloor = FD_getFloor();
                    // check command and up queue
                    if (FIFO_floorInQueue(&EL_commandQueue, currentFloor) || FIFO_floorInQueue(&EL_callUpQueue, currentFloor)){
                        // should stop here
                        FIFO_popFloor(&EL_commandQueue, currentFloor);
                        FIFO_popFloor(&EL_callUpQueue, currentFloor);
                        state = state_arrived;
                    }

                    // check down queue if others are empty
                    if (FIFO_isEmpty(&EL_callUpQueue) && FIFO_isEmpty(&EL_commandQueue) && FIFO_floorInQueue(&EL_callDownQueue, currentFloor))
                    {
                        FIFO_popFloor(&EL_callDownQueue, currentFloor);
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

                if (EL_checkAndUpdateOrders()){
                    EL_updateQueueLights();
                }

                if (FD_isOnFloor()){

                    int currentFloor = FD_getFloor();
                    // check command and up queue
                    if (FIFO_floorInQueue(&EL_commandQueue, currentFloor) || FIFO_floorInQueue(&EL_callDownQueue, currentFloor)){
                        // should stop here
                        FIFO_popFloor(&EL_commandQueue, currentFloor);
                        FIFO_popFloor(&EL_callDownQueue, currentFloor);
                        state = state_arrived;
                    }

                    // check down queue if others are empty
                    if (FIFO_isEmpty(&EL_callDownQueue) && FIFO_isEmpty(&EL_commandQueue) && FIFO_floorInQueue(&EL_callUpQueue, currentFloor))
                    {
                        FIFO_popFloor(&EL_callUpQueue, currentFloor);
                        state = state_arrived;
                    }
                }
                break;

            case state_stop:
                EL_stop();
                state = state_standby;
                break;

            case state_arrived:
                if (HW_getStopSignal()){
                    state = state_stop;
                    break;
                }

                // assumes correct floor
                HW_setMotorDirection(DIRN_STOP);
                EL_checkAndUpdateOrders();
                EL_updateQueueLights();
                
                if (!doorTimerStarted){
                    printf("TIMER started\n");
                    TIMER_set(DOOR_OPEN_TIME);
                    TIMER_start();
                    DC_openDoor();
                    doorTimerStarted = 1;
                }

                if (TIMER_timeout()){
                    printf("TIMER timeout\n");
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