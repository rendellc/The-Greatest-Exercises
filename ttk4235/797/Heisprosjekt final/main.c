#include "elev.h"
#include "executive.h"
#include "buttonspressed.h"
#include "input.h"
#include <stdio.h>
#include <unistd.h>



int main() {
    // Initialize hardware


    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    initialize();

    while (1) {
        last_floor(); //Heisen vil alltid ha kontroll på hva som var siste etasje passert.
        order_placed(); //Pollingen av knappene vil sje kontinuerlig.
        set_light(); //Hvilke lys som skal av/på settes også kontinuerlig.
        set_floor_lamp(); //Hvilket etasjelys som skal settes, bestemmes også kontinuerlig.
        stop(); //Sjekker om heisen får input fra stoppknappen. Agerer utifra dette.
        if(stop_or_not() == 1){ 
        	double timer = set_timer(); //Hvis heisen stopper i en etasje, starter timeren som teller 3s for åpen dør.
        	while(compare_timer(timer) == 0){ //Løkken gjør at heisen fungerer som normalt (tar i mot bestillinger, setter lys og poller stoppknappen) når den står i en etasje og behandler en bestilling. 
                    order_placed();
        			set_light();
                    if(stop_or_not() == 1){ //Blir en opp-/ned- eller etasjeknapp for samme etasje som heisen befinner seg i, trykket. Skal timeren på døren resettes.
                        timer = set_timer();
                    }
                    stop();
        			elev_set_motor_direction(0);

        	}
            doorOpen = 0;
       		elev_set_door_open_lamp(0);
       	}
        set_direction(); //På slutten av løkken settes currentDir basert på bestillingene man har fått inn.   	
       	set_motor_direction();
        
    }
    return 0;
}
