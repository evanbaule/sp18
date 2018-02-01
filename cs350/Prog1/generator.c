#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "common.c"

int main(int argc, char *argv[], char *envp[])
{
	/*
	 * INITIALIZATION
	 */
	/* default -> opt -n */
	int numIntegers = 100;

	/* default -> opt -m */
	int boundsMinimum = 1;

	/* default -> opt -M */
	int boundsMaximum = 255;

	/* default -> opt -s */
	int seed = time(0);
	struct timeval* timev1 = NULL;
	gettimeofday(timev1, NULL);

	/* default -> opt -o */
	FILE* outputStream = stdout;

	/* parse optargs */
    int option;
    while ((option = getopt(argc, argv,"un:m:M:s:o:")) != -1) 
    {
	switch (option) 
	{
		case 'u' : 
			//usage mode 1 assigned to generator
			printUsageString(1);
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

		case 's' : 
			seed = atoi(optarg);
			break;

		case 'o' : 
			outputStream = fopen(optarg, "w");
			//printf("outputStream opened at: %s\n", optarg);
			break;

		default: 
			printf("uhh something went wrong when opt parsing:( \n");
			exit(EXIT_FAILURE);
		}
    }

    /*
     * POST INIT INPUT VALIDATION
     */
    //Potentially redundant check in case ordering of opts breaks
    if(boundsMinimum > boundsMaximum)
    {
    	perror("Invalid generation bounds: concluded that minimum bound is greater than maximum bound (max < min)");
    	exit(EXIT_FAILURE);
    }

    /*
	 * GENERATOR EXECUTION
	 */
	/* Output total to file line 1, used in sorting */
	fprintf(outputStream, "%d\n", numIntegers);

	/* Generation Loop */
	srand(seed);
	int it = 0;
	while(it < numIntegers)
	{
		int rando = rand() % (boundsMaximum + 1 - boundsMinimum) + boundsMinimum;
		//printf("x: %d\n", rando);
		fprintf(outputStream,"%d\n", rando);
		it++;	
	}	

	return 0;
}
