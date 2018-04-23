#pragma once
#include "HW_driver.h"
#


typedef HW_buttonType_t LC_lightType_t;

typedef struct{
	int floor;
	LC_lightType_t type;
} LC_light_t;



void LC_lightOn(LC_light_t light);

void LC_lightOff(LC_light_t light);

void LC_updateFloorIndicators();