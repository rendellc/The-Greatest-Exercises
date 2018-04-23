#include "HW_driver.h"
#include "FloorDetector.h"
#include "DoorController.h"
#include "Timer.h"
#include <stdio.h>
#include <stdbool.h>




int main() {
    // Initialize hardware
    if (!HW_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Hardware setup complete\n");

    EL_mainloop();

    return 0;
}
