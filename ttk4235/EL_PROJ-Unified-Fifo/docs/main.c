#include "HW_driver.h"
#include "FloorDetector.h"
#include "DoorController.h"
#include "Timer.h"
#include "LightController.h"
#include <stdio.h>
#include <stdbool.h>




int main() {
    // Initialize hardware
    if (!HW_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Hardware setup complete\n");


    TIMER_set(1000);
    TIMER_start();

    while (!TIMER_timeout());


	printf("Wait complete\n");
    printf("HW_getStopSignal = %d\n", HW_getStopSignal());
    EL_mainloop();


    return 0;
}
