#ifndef _INCLUDE_TIMER_H_
#include <time.h>

double get_wall_time(void); //Gir oss antall sekunder siden 1. januar 1970

void t_start_timer();
int t_wait_3_sec(); //Returnerer 1 etter at det har gått 3 sekunder

#endif