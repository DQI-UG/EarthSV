#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "TextIO.h"
#include "constants.h"

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60


void printEpsilons(int historyLength, unsigned long long int sourceLength,
		long double *epsilons) {
	//printing epsilons
	if (info)
			printf("\n\nINFO: source length: %lld \n", sourceLength);
	if (info)
		printf("\n\nINFO:  Epsilons\n\n");
	for (int i = 0; i <= historyLength; i++) {
		//printf("Maximal epsilon for history of length %d is %.15Lf\n", i, maxEpsilons[i]);
		printf("Epsilon for history length %.2d = %.15Lf\n", i, epsilons[i]);
		//if (maxEpsilons[i] > maxEpsilon) {
		//	maxEpsilon = maxEpsilons[i];
		//}
	}
	if (info)
		printf("\n\nINFO:  Epsilons end \n\n");

	//if (info) printf("\nINFO: Maximal epsilon was %.15Lf\n\n", maxEpsilon);
	//if (info)
		//printf("INFO: lg(lg(length)) = %Lf\n\n", log2l(log2l(sourceLength)));
}

void printData(unsigned long long int* sequenceCounts, int sequenceLength)
{
	for(int i = 0; i < sequenceLength; i++) printf("%lld ", sequenceCounts[i]);
	putchar('\n');
}

void printProgress(double percentage) {
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush(stdout);
}