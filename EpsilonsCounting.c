#include "EpsilonsCounting.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "constants.h"
#include "SequencesCounting.h"
#include "TextIO.h"

long double* calculateEpsilons(unsigned char *data, unsigned long long int sourceLength, int historyLength) {

	long double *epsilons;
	unsigned long long int *sequencesCount[MAXHISTORY]; //30 is max history here
	long double currentEpsilon = 0;

	if (debug)	printf("new version\n");

	//allocating arrays for epsilons
	// I have no idea why historyLength+1 not working here!
	epsilons = (long double*) malloc((historyLength +1) * sizeof(long double));
			if (epsilons == NULL) {
				fprintf(stderr, "mainSV: malloc %lu failed\n",
						2 * historyLength * sizeof(long double));
				exit(1);
			}

			for (int i = 0; i <= historyLength; i++) {
				epsilons[i] = 0;
			}

	//allocating arrays for frequencies
	for (unsigned long long int i = 0, power = 2; i <= historyLength; i++) {
		sequencesCount[i] = (unsigned long long*) malloc(
				power * sizeof(unsigned long long int));
		if (sequencesCount[i] == NULL) {
			fprintf(stderr, "mainSV: malloc %lld failed\n",
					power * sizeof(unsigned long long int));
			exit(1);
		}
		for (unsigned long long j = 0; j < power; j++) {
			sequencesCount[i][j] = 0;
		}
		power *= 2;
	}


	//counting sequences
	for (int i = 0; i <= historyLength; i++) {
		if (info)
			printf("INFO: Processing SV with history of length %d\n", i);
		countSequences(data, sourceLength, sequencesCount[i], i);
	}


	const long long int printLimit = 5;
	if (debug) {
		printf("\nDEBUG: Processed, frequences are\n\n");

		for (int i = 0; i <= historyLength; i++) {
			if (i < printLimit)
				printData(sequencesCount[i], pow(2, i + 1));
		}
		if (debug)
			printf("DEBUG: ...\n");
	}

	if (debug)
		printf("\nDEBUG: Epsilon estimations\n\n");

	//calculating epsilons
	currentEpsilon = fabsl(
			sequencesCount[0][0] / (long double) sourceLength - 0.5);
	epsilons[0] = currentEpsilon;

	if (debug)	printf("DEBUG: %.15Lf\n", currentEpsilon);

	for(unsigned long long int i = 1, power = 4; i <= historyLength; i++) {
		for(unsigned long long j = 0; j < power; j += 2) {
			currentEpsilon = fabsl(sequencesCount[i][j]	/ (long double) sequencesCount[i-1][j/2] - 0.5);
			if(currentEpsilon > epsilons[i]) {
				epsilons[i] = currentEpsilon;
			}
			if(i < printLimit) {
				if (debug) {
					printf("%.15Lf ", currentEpsilon);
				}
			}
		}
		power *= 2;
		if(i < printLimit) {
			if (debug) printf("\n");
		}
	}

	if (debug)
		printf("DEBUG: source length: %lld \n", sourceLength);

	for (unsigned long long int i = 0; i <= historyLength; i++) {
		free(sequencesCount[i]);
	}


	return epsilons;
}
