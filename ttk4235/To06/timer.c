#include <stdio.h>
#include <sys/time.h>

#include "timer.h"

double start_time;
double end_time;
//double secs;

double get_wall_time(void){
    struct timeval time;
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001;
}


void t_start_timer() {
	start_time = get_wall_time();
	end_time = start_time + 3;
}

int t_wait_3_sec() {
	double poll_time = get_wall_time();
	double secs = poll_time-start_time;
	//printf("%f\n",secs);
	
	if (poll_time >= end_time){
		start_time = 0;
		end_time = 0;
		return 1;
	}
	return 0;

}



