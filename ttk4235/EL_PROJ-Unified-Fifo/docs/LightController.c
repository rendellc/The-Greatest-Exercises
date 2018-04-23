#include "LightController.h"


void LC_lightOn(LC_light_t light){
    HW_setButtonLamp(light.type, light.floor, 1);
}

void LC_lightOff(LC_light_t light){
    HW_setButtonLamp(light.type, light.floor, 0);
}

void LC_updateFloorIndicators(){
    int currentFloor = HW_getFloorSensorSignal();

    if (currentFloor != -1){
        HW_setFloorIndicator(currentFloor);
    }    
}
