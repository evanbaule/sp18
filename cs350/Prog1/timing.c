#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval* timingStart;
struct timeval* timingEnd;

/* Return current system time */
struct timeval* getCurrentTime()
{
	struct timeval* cur = NULL;
	gettimeofday(cur, NULL);
	return cur;
}

/* Starts timer */
void startTiming()
{
	gettimeofday(timingStart, NULL);
}
/* Ends timer and returns the difftime() between end - start */
double endTiming()
{
	gettimeofday(timingEnd, NULL);
	return 0;
	//return difftime(timingEnd, timingStart);
}
