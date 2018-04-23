#include "elev.h"
#include "fsm.h"
#include "qs.h"
#include "timer.h"
#include <stdio.h>



int main() {
 
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    //INITIALISERING START - Setter heisen i en definert etasje

    if (elev_get_floor_sensor_signal() == -1)
    {
        elev_set_motor_direction(DIRN_UP); //Kjører heisen til etasjen over hvis den befinner seg i udefinert tilstand
    }

    while(1){ //Bryter ut av loopen når heisen ankommer en etasje
        
        if (elev_get_floor_sensor_signal() != -1){  

            qs_set_current_floor(elev_get_floor_sensor_signal());
            qs_set_next_floor(qs_get_current_floor());
            qs_set_last_dir(DIRN_UP);

            elev_set_motor_direction(0);

            qs_set_current_dir(0);                               

            print_current_floor();
            print_next_floor();
            break;
        }
        
    }

    //INITIALISERING SLUTT

    //HOVED-LØKKE START

    while(1) {


        if (elev_get_floor_sensor_signal() == qs_get_next_floor()){ //Trigger til arrived_floor
            //print_current_floor();
            //print_next_floor();
            fsm_arrived_floor();

            if(elev_get_stop_signal()){ //Trigger til stop_elevator. 
                fsm_stop_elevator();


            }

        }
        print_current_floor();
        print_next_floor();
        printf("\n");
        print_matrix();
        printf("\n");

        printf("Amount of orders: %d \n", qs_get_number_of_orders());

        if ((qs_get_number_of_orders() > 0)) { //Trigger til drive_elevator
            printf("Kjør\n");
            fsm_drive_elevator();

            if(elev_get_stop_signal()) { //Trigger til stop_elevator
                fsm_stop_elevator();


            }

        }
        //print_matrix();
    
    }
    return 0;
}

    //HOVEDLØKKE SLUTT
