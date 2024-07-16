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


unsigned long long int countData(char *fileName) {
	unsigned long long int counter = 0;
	double entry = 0;
	FILE *file = NULL;
	struct stat st;
	off_t fileSize = 1;
	off_t aproximateFileLength = 1;
	int scanfResoult = 0;
	char * tempLine = NULL;
	size_t tempLineLength = 0;

	if(stat(fileName, &st) != -1){
		fileSize = st.st_size;
		aproximateFileLength = fileSize / 25;
		if (info)
			printf("INFO: Aproximate file size = %ld\n", fileSize);
	}
	file = fopen(fileName, "r");
	if (file == NULL) {
			fprintf( stderr, "count_data: opening file %s failed", fileName);
			exit(1);
	}
	while (1) {
		scanfResoult = fscanf(file, "%lf", &entry);
		//printf("bla = %d\n", scanfResoult);
		if(scanfResoult == EOF) break;
		if(scanfResoult < 1) {
			getline(&tempLine, &tempLineLength, file);
			continue;
		}
		if(aproximateFileLength > 100) {
			if(100 * counter % ((aproximateFileLength / 100) * 100)  == 0) {
				printProgress(((double) counter) / aproximateFileLength);
			}
		}
		counter++;
	}
	fclose(file);
	return counter;
}

long double* loadData(char *fileName, unsigned long long int *length) {
	unsigned long long int i = 0;
	long double *dataTable = NULL;
	FILE *file = NULL;
	long double entry = 0;
	int scanfResoult = 0;
	char * tempLine = NULL;
	size_t tempLineLength = 0;

	file = fopen(fileName, "r");
	if (file == NULL) {
			fprintf( stderr, "load_data: opening file %s failed", fileName);
			exit(1);
	}
	dataTable = (long double*) malloc(*length * sizeof(long double));
	while (1) {
		scanfResoult = fscanf(file, "%Le", &entry);
		//printf("bla = %d\n", scanfResoult);
		if(scanfResoult == EOF) break;
		if(scanfResoult < 1) {
			getline(&tempLine, &tempLineLength, file);
			continue;
		}
		dataTable[i] = entry;
		if(*length > 100){
			if(100*i % ((*length / 100) * 100)  == 0) {
				printProgress(((double) i) / *length);
			}
		}
		i++;
		if(i>=numberOfLines) break;
	}
	if (info)
		printf("\nINFO: Number of loaded data entries = %lld\n", i);
	fclose(file);
	return dataTable;
}

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