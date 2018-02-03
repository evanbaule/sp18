#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include "timing.c"
#include "common.c"

char* getActiveUser();
int compare (const void * a, const void * b);

int main(int argc, char *argv[], char *envp[])
{
	/*
	 * INITIALIZATION
	 */
	char* activeUser = getActiveUser();

	/* default -> opt -n */
	int numIntegers = 100;

	/* default -> opt -m */
	int boundsMinimum = 1;

	/* default -> opt -M */
	int boundsMaximum = 255;
	
	/* default -> opt -i */
	FILE* inputStream = stdin;

	/* default -> opt -o */
	FILE* outputStream = stdout;

	/* default -> opt -c */
	FILE* c_outputStream = stdout;

	/* parse optargs */
	int option;
	while ((option = getopt(argc, argv,"un:m:M:s:i:o:c:")) != -1) 
	{
	switch (option) 
	{
		case 'u' : 
			//usage mode 0 assigned to sorter
			printUsageString(0);
			break;
		case 'n' : 
			numIntegers = atoi(optarg);
			if(numIntegers < 0 || numIntegers >= 1000000)
			{
				perror("Invalid Opt: Input to -n must be between 0 and 1,000,000");
				exit(EXIT_FAILURE);
			}
			break;

		case 'm' : 
			boundsMinimum = atoi(optarg);
			if(boundsMinimum < 1)
			{
				perror("Invalid Opt: Input to -m must be at least 1");
				exit(EXIT_FAILURE);
			}
			else if(boundsMinimum > boundsMaximum || boundsMinimum > 1000000)
			{
				perror("Invalid Opt: Input to -m must be LESS than input to -M.");
				exit(EXIT_FAILURE);
			}
			break;

		case 'M' : 
			boundsMaximum = atoi(optarg);
			if(boundsMaximum > 1000000 || boundsMinimum < 1)
			{
				perror("Invalid Opt: Input to -M cannot exceed 1,000,000");
				exit(EXIT_FAILURE);
			}
			else if(boundsMinimum > boundsMaximum)
			{
				perror("Invalid Opt: Input to -M must be MORE than input to -m.");
				exit(EXIT_FAILURE);
			}
			break;
		case 'o' : 
			outputStream = fopen(optarg, "w");
			//printf("outputStream opened at: %s\n", optarg);
			break;
		case 'i':
			inputStream = fopen(optarg, "r");
			//printf("inputStream opened at: %s\n", optarg);
			break;
		case 'c':
			c_outputStream = fopen(optarg, "w");
			//printf("c_outputStream opened at: %s\n", optarg);
			break;
		default: 
			printf("uhh something went wrong when opt parsing:( \n");
			exit(EXIT_FAILURE);
		}
    }

    /* Redundant check for invalid input to -m || -M */
    if(boundsMinimum > boundsMaximum)
    {
    	perror("Invalid generation bounds: concluded that minimum bound is greater than maximum bound (max < min)");
    	exit(EXIT_FAILURE);
    }

    //Starts runtime measurement
    struct timeval startTime;
    gettimeofday(&startTime, NULL);

    /* Retrieve input from line 1 of -i input file */
	int inputSize = -1;
	if(fscanf(inputStream, "%d", &inputSize) != EOF)
    {
    	//printf("INPUT_SIZE: %d\n", inputSize);
    } else 
    {
    	perror("Invalid input: file specified by -i is empty");
    }
    /* Check for invalid input to -n where the two specified numbers don't match*/
    if(numIntegers != inputSize)
    {
    	perror("Invalid input: input -n does not match the size of the file specified by -i");
    }

	/*
	 * SORT EXECUTION
	 */	
	int *inputArray;
	inputArray = (int *) malloc (inputSize * sizeof(int));
	if(inputArray)
	{
		/* Parse input stream for integers to feed into inputArray */
    	int it;
    	for(it = 0; it < inputSize; it++)
    	{
    		int inputBuffer = -1;
    		fscanf(inputStream, "%d", &inputBuffer);
			if(inputBuffer >= boundsMinimum && inputBuffer <= boundsMaximum)
			{
				inputArray[it] = inputBuffer;
			} else 
			{
				perror("Input value does not fall within the specified bounds");
				exit(EXIT_FAILURE);
			}
    	}
	    /* Sorting integer array */
		qsort(inputArray, inputSize, sizeof(int), compare);

		/* Put sorted array to specified (d stdout) output stream */
		int ip;
		for(ip = 0; ip < inputSize; ip++)
		{
			fprintf(outputStream, "%d\n", inputArray[ip]);
		}

	} else 
	{
		perror("Memory allocation failed.\n");
	}

	//BASELINE NEED IMPROVEMENT
	/* runtime independant printing of username values */
	int userlen = (int)strlen(activeUser);
	int* asciiCounter = (int*) malloc(userlen * sizeof(int));
	int j;
	//init to all 0s
	for(j = 0; j < userlen; j++)
	{
		asciiCounter[j] = 0;
	}
	if(asciiCounter)
	{
		//printf("USERLEN:\t%d\n", userlen);
		int it;
		for(it = 0; it < userlen; it++)
		{
			int it2;
			for(it2 = 0; it2 < inputSize; it2++)
			{
				if(inputArray[it2] == activeUser[it])
				{
					asciiCounter[it]++;
				}
			}
		}
		//printf("PRINTING USER DETAILS\n");
		int it3;
		for(it3 = 0; it3 < userlen; it3++)
		{
			//remember to change to c_outputstream
			fprintf(c_outputStream, "%c\t%d\t%d\n", activeUser[it3], (int)activeUser[it3], asciiCounter[it3]);
		}
	}
	struct timeval endTime;
	gettimeofday(&endTime, NULL);
	float runtime = timeDifference(&startTime, &endTime);
	//printf("%ld.%06ld\n", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec)
	fprintf(stderr, "Elapsed Runtime: %.3f\n", runtime);
	return 0;
}

char * getActiveUser() 
{
	return getenv("USER");
}

/* qsort() helper function */
int compare (const void * a, const void * b)
{
	/* credit: http://www.cplusplus.com/reference/cstdlib/qsort/ */
	return ( *(int*)a - *(int*)b );
}
