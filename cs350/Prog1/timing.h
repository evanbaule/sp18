#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval timingStart;
struct timeval timingEnd;

struct timeval* getCurrentTime();
void startTiming();
float timeDifference(struct timeval* t1, struct timeval* t0);