#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

const char* generatorUsageString = "prog1generator [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>] [-o <output-file-name>]";
const char* sorterUsageString = "prog1sorter [-u] [-n <num-integers>] [-m <min-int>] [-M <max-int>][-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]";

void printUsageString(int mode)
{
	switch(mode){
		case 0: 
			fprintf(stderr, "%s\n", sorterUsageString);
			exit(EXIT_SUCCESS);
			break;
		case 1:
			fprintf(stderr, "%s\n", generatorUsageString);
			exit(EXIT_SUCCESS);
			break;
		default:  
			printf("Invalid usage parameter - usage string generation failed. Programmer fault. \nUsage of printUsageString(): void printUsageString(int mode) where :mode is mapped to a known program's stored usage string.\n");
			exit(EXIT_FAILURE);
			break;
	}
}
