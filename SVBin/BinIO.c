#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BinIO.h"

#define DEBUG 0

unsigned long long int countBinData(char* filename)
{
	unsigned long long int count = 0;
	unsigned char byte[1] = {0};
	FILE* f = fopen(filename, "rb");
	if (f == NULL)
    {
        fprintf( stderr, "countBinData: opening file %s failed", filename);
        exit(1);
    }

	while(fread(byte,sizeof(unsigned char), 1, f) && !feof(f)) count++;
	fclose(f);

	return count;
}

unsigned char* loadBinData(char* filename, unsigned long long int* count)
{
	unsigned long long int i = 0;
	unsigned char byte;
	unsigned char power;
	unsigned char* cdatas = NULL;
	FILE* f = NULL;
	byte = 0;

	f = fopen(filename, "rb");
	if (f == NULL)
    {
        fprintf( stderr, "loadBinData: opening file %s failed", filename);
        exit(1);
    }
	cdatas = (unsigned char*) malloc(*count * sizeof(char) * 8);
	if (cdatas == NULL)
    {
        fprintf( stderr, "loadBinData: malloc %lld failed", *count * sizeof(char) * 8);
        exit(1);
    }
	printf("Allocated %lld bytes of memory\n", *count * sizeof(char) * 8);
	//printf("Allocated %ld bits of memory\n", sizeof(char));

	while (i < (*count)) {
	power=128;
		fread(&byte,sizeof(unsigned char), 1, f); /* reading by char, although they are positive */
		if(DEBUG) printf("\n old = %d \n", byte);
			for (int j=0; j<8; j++){ /*order opposite to writing */
				if ((byte & power)>0) {
					cdatas[8*i + j]=1;
				}
				else {
					cdatas[8*i + j]=0;
				}
				if(DEBUG) printf("\n power = %u \n", power);
				power = power >> 1;
			}
		i++;
	}

	return cdatas;
}