#include "SequencesCounting.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*** FUNCTION DEFINITIONS ***/

void countSequences(unsigned char* datas, unsigned long long int sourceLength, unsigned long long int* sequencesCount, int historyLength)//TODO check +-1 ranges, types ect
{
	unsigned long long int sequence = 0;
	unsigned long long int oldestBitDeleter = (1 << historyLength) - 1;

	sequence = datas[0];
	for(unsigned long long int i = 1; i <= historyLength; i++){
		sequence = sequence << 1;
		sequence += datas[i];
	}
	sequencesCount[sequence]++;
	for(unsigned long long int i = historyLength + 1; i < sourceLength; i++){
		sequence = sequence & oldestBitDeleter;
		sequence = sequence << 1;
		sequence += datas[i];
		sequencesCount[sequence]++;
	}
}
