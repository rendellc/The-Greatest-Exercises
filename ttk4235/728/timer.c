//
//  Timer.c
//  HeisprosjektTest
//
//  Created by Andrea Holten on 23.02.2017.
//  Copyright © 2017 Andrea Holten. All rights reserved.
//
#include "timer.h"
#include <stdio.h>
#include <sys/time.h>

static double start_timer;
static int timer_running = 0;

/* Start og stopp av timer
 
 timer_start();
 
 if (timer_end()){
 printf("Timer er slutt!");
 }
 
*/

static double time_in_seconds(void){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec+(double)time.tv_usec*0.000001;
}

void timer_start(void){
    start_timer = time_in_seconds();
    timer_running = 1;
    return;
}

int timer_end(void){
    double current_time = time_in_seconds();

    if (((current_time - start_timer) > 3) && timer_running == 1 ){
    	timer_running = 0;
    	return 1;
    }
    return 0; 
}

