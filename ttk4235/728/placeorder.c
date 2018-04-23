//
//  PlaceOrder.c
//  HeisprosjektTest
//
//  Created by Andrea Holten on 23.02.2017.
//  Copyright © 2017 Andrea Holten. All rights reserved.
//

#include <stdio.h>
#include "placeorder.h"



/* 
0-2 Button up - 1,2,3
3-5 Button down - 2,3,4
6-9 Button command - 1,2,3,4
*/

static int queue[10] = {0};


int po_add_order(int button_type, int floor){
    int index;
    if (button_type == 0 || button_type == 2){
        index = (button_type*3) + (floor);    //Opp- og internknapp
    }
    else{
        index = (button_type*3) + (floor-1);    //nedknapp
    }
    
    if (queue[index] == 0){
        queue[index] = 1;
        return 1;
    }
    return 0; 
}


void po_delete_order(int button){
    queue[button] = 0;
}


void po_delete_all_orders(){
    for(int i = 0; i < 10 ; i++){
        queue[i] = 0;
    }
}


int po_check_order(int floor){
    return queue[floor];
}
