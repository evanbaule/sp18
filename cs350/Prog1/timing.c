#include "timing.h"

struct timeval timingStart;
struct timeval timingEnd;

/* Return current system time */
struct timeval* getCurrentTime()
{
	struct timeval* cur = NULL;
	gettimeofday(cur, NULL);
	return cur;
}

float timeDifference(struct timeval* t1, struct timeval* t0)
{	
	//t0 as starting time, t1 as ending time
	//printf("calculating time differential.... \n");
	return ((t0->tv_sec - t1->tv_sec) + ((float) (t0->tv_usec - t1->tv_usec)) / 1000000);
}
