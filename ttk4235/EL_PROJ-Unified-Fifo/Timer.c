#include <time.h>
#include <stdbool.h>

static clock_t TIMER_startTime;
static int TIMER_setTime;

void TIMER_start() {
	TIMER_startTime = clock();
}

void TIMER_set(int msSet) {
	TIMER_setTime = msSet;
}

bool TIMER_timeout() {
	clock_t diff = clock() - TIMER_startTime;
	int diffms = diff * 1000 / CLOCKS_PER_SEC;

	return (diffms > TIMER_setTime);
}




/*
clock_t start = clock();
sleep(3);
clock_t end = clock();
double elapsed_time = (end - start)/(double)CLOCKS_PER_SEC;
printf("Elapsed time: %.2f.\n", elapsed_time);


#include <time.h>

clock_t start = clock(), diff;
ProcessIntenseFunction();
diff = clock() - start;

int msec = diff * 1000 / CLOCKS_PER_SEC;
printf("Time taken %d seconds %d milliseconds", msec/1000, msec%1000);

*/
