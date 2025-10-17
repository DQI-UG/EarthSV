#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <argp.h>
#include <argz.h>

#include "constants.h"
#include "Discretizations.h"
#include "EpsilonsCounting.h"
#include "Manuals.h"
#include "Mathematical.h"
#include "SequencesCounting.h"
#include "BinIO.h"
#include "TextIO.h"
#include "FinalEpsilon.h"

int info = 1;
int debug = 1;

/*** PROTOTYPES ***/

int mainSV(int argc, char **argv);
int calculateFormulaMaxHistoryLength (unsigned long long int n);


/*** MAIN ***/
int main(int argc, char **argv) {
	clock_t startTime = clock();

	mainSV(argc, argv); //main function for SV estimation

    clock_t endTime = clock();
    double runningTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
    if (info) printf("\nINFO: Program running time was %lf seconds\n", runningTime);
    return 0;
}


int mainSV(int argc, char **argv)
{
    unsigned char *binData = NULL;
	long double *epsilons = NULL;
	// unsigned long long int sourceLength = 0;
    long double finalEpsilon;
    char *p;
    unsigned long long int number_of_bytes = 0;
    int historyLength = MAXHISTORY;

    if (info)
    {
		printf("INFO: Verbose version\n");
    	printf("INFO: Data file: %s\n", argv[1]);
        printf("INFO: Number of paramteters: %d\n", argc);
    }

    if(argc <= 2) {

        if (info)
        {
		printf("INFO: Counting file lines\n");
        }

        number_of_bytes = countBinData(argv[1]);

        printf("\nThe number of lines in the file %lld\n", number_of_bytes);
    }
    else 
    {
        printf("INFO: second parameter: %s\n", argv[2]);
        number_of_bytes = strtoull(argv[2], &p, 10);
        printf("\nThe number of lines manually set %lld\n", number_of_bytes);
    }


    if (info) printf("INFO: Loading data from file\n");

	binData = loadBinData(argv[1], &number_of_bytes);//loading data from file

	if (info)printf("INFO: Data loaded\n");
    if (info) printf("INFO: Using history of length %d\n", historyLength);
    if (info) printf("INFO: Program takes %lld lines from data file.\n",number_of_bytes);

	if (debug)
		printf("DEBUG: Source length %lld\n",number_of_bytes);
	if (debug)
		printf("DEBUG: File loaded\n");
	epsilons = calculateEpsilons(binData, number_of_bytes, historyLength);//main calculation of frequencies and epsilons
	printEpsilons(historyLength, number_of_bytes, epsilons); //printing epsilons

    finalEpsilon = FinalEpsilon(epsilons, calculateFormulaMaxHistoryLength(number_of_bytes), historyLength, 1,2);
    if (finalEpsilon < 0) printf("The function FinalEpsilon invoked with  wrong parameters");
    printf("Final epsilon based on powers for history length %d %.15Lf\n ",calculateFormulaMaxHistoryLength(number_of_bytes),finalEpsilon);  

    free(binData);
    free(epsilons);

    return 0;
}

int calculateFormulaMaxHistoryLength(unsigned long long int n)
{
    int hl =(int)(floorf((float)logl((long double)n)/logl(2))) -1;
    return hl;
}
