/* Prototypes for the functions */

unsigned long long int countData(char *filename);

long double* loadData(char *filename, unsigned long long int *count);

void printEpsilons(int historyLength, unsigned long long int sourceLength,
		long double *epsilons);

void printData(unsigned long long int* datas, int count);

void printProgress(double percentage);
