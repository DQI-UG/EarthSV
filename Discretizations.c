#include <stdio.h>
#include <stdlib.h>
#include "Discretizations.h"


unsigned char* minMaxPreprocessing(unsigned char* datas, unsigned long long int* lnin, int cS, int cA){
	unsigned char* dataout = NULL;

	dataout = (unsigned char*) malloc(*lnin * sizeof(unsigned char));
	if (dataout == NULL)
    {
        fprintf( stderr, "load_data: malloc %lld failed", *lnin * sizeof(unsigned char));
        exit(1);
    }

int jmax;//lnin=21;
int condition=0;

int initial=0;
int i=0;
int index=0;
//int d;
int flag;

do
{
	int count=0;
	int j=1;
	if (condition==0)
	{
		//cout << "first loop working" << endl;

		if(datas[i]==0)
		{
			jmax=cS;
			do
			{
				if(datas[i+j]==datas[i+j-1])
				{
				count++;
				}
				j++;
			}while(j<=jmax-1);
		}
		j=1;

		if(datas[i]==1)
		{
			int jmax=cA;
			do
			{
				if(datas[i+j]==datas[i+j-1])
				{
				count++;
				}
				j++;
			}while(j<=jmax-1);
		}
		j=1;
	}

	else
	{
		//cout << "condition=" << condition << endl;
		if(flag==0)
		{
			jmax=cS;
		}
		if(flag==1)
		{
			jmax=cA;
		}
		do
		{
			if(datas[i+j]==flag && datas[i+j-1]==flag)
			{
			count++;
			}
			j++;
		}while(j<=jmax-1);
		j=1;
	}


	if(count==jmax-1)
	{
		//cout << "i=" << i << endl;
		//cout << "count=" << count << endl;
		condition++;
		if(datas[i]==0)
		{
			flag=1;
		}
		else
		{
			flag=0;
		}
		//cout << "flag=" << flag << endl;

		//d=i-initial;
		//printf( "number of intermediate strings d is %d\n", d);
		//<< "\t" << "initial=" << initial << endl;
		int sum=0;
		for(int k=initial; k<=i-1; k++)
		{
		sum = sum + datas[k];
		}
		//cout << "sum=" << sum << endl;
		int binary=sum%2;
		//cout << "binary=" << binary << "index=" << index << endl;
		dataout[index] = binary;
		//cout << dataout << endl;
		index++;
		initial=i+jmax;
		i=initial-1;
	}
i++;
}while(i <= *lnin - jmax);
printf( "maximum element number of binary string is %d\n", index);
*lnin = index;
/*
printf( "output binary string is\n");
for(int l=0; l<d; l++)
{
	printf("%d\n",dataout[l]);
}
*/
	//return medicalDatasDiscretized; //remove this line when function redy!
	return dataout;
}

unsigned char* discretization1(long double* datas, unsigned long long int* count, int etha)
{
	unsigned char* datas_disc = NULL;

	datas_disc = (unsigned char*) malloc(*count * sizeof(unsigned char));
	if (datas_disc == NULL) {
        fprintf( stderr, "load_data: malloc %lld failed", *count * sizeof(unsigned char));
        exit(1);
    }
	for(unsigned long long int i=0; i < *count; i++) {
		if(datas[i] >= 0) datas_disc[i] = 0;
		else datas_disc[i] = 1;
	}
	return datas_disc;
}

unsigned char* discretization2(long double* datas, unsigned long long int* count, int etha)
{
	unsigned char* datas_disc = NULL;
	long double sum = 0;
	long double mean = 0;

	for(unsigned long long int i=0; i < *count; i++) {
		sum += datas[i];
	}
	mean = sum / *count;
	printf("sum = %Le count = %llu mean = %Le\n", sum, *count, mean);
	datas_disc = (unsigned char*) malloc(*count * sizeof(unsigned char));
	if (datas_disc == NULL) {
        fprintf( stderr, "load_data: malloc %lld failed", *count * sizeof(unsigned char));
        exit(1);
    }
	for(unsigned long long int i=0; i < *count; i++) {
			if(datas[i] >= mean) datas_disc[i] = 0;
			else datas_disc[i] = 1;
		}
	return datas_disc;
}

unsigned char* discretization3(long double* datas, unsigned long long int* count, int etha)
{
	unsigned char* datas_disc = NULL;
	long double sum = 0;
	long double mean = 0;

	for(unsigned long long int i=0; i < *count; i++) {
			if(datas[i] < 0) {
				datas[i] = -datas[i];
			}
		}
	for(unsigned long long int i=0; i < *count; i++) {
		sum += datas[i];
	}
	mean = sum / *count;
	printf("sum = %Le count = %llu mean = %Le\n", sum, *count, mean);
	datas_disc = (unsigned char*) malloc(*count * sizeof(unsigned char));
	if (datas_disc == NULL) {
        fprintf( stderr, "load_data: malloc %lld failed", *count * sizeof(unsigned char));
        exit(1);
    }
	for(unsigned long long int i=0; i < *count; i++) {
			if(datas[i] >= mean) datas_disc[i] = 0;
			else datas_disc[i] = 1;
		}
	return datas_disc;
}

unsigned char* discretization4(long double* datas, unsigned long long int* count, int etha)
{
	unsigned char* datas_disc = NULL;

	datas_disc = (unsigned char*) malloc(*count * sizeof(unsigned char));
	if (datas_disc == NULL) {
        fprintf( stderr, "load_data: malloc %lld failed", *count * sizeof(unsigned char));
        exit(1);
    }
	datas_disc[0] = 0;
	for(unsigned long long int i=1; i < *count; i++) {
		if(datas[i] >= datas[i-1]) datas_disc[i] = 0;
		else datas_disc[i] = 1;
	}
	return datas_disc;
}

unsigned char* discretization5(long double* datas, unsigned long long int* count, int etha)
{
	unsigned char* datas_disc = NULL;

	for(unsigned long long int i=0; i < *count; i++) {
			if(datas[i] < 0) {
				datas[i] = -datas[i];
			}
		}
	datas_disc = (unsigned char*) malloc(*count * sizeof(unsigned char));
	if (datas_disc == NULL) {
        fprintf( stderr, "load_data: malloc %lld failed", *count * sizeof(unsigned char));
        exit(1);
    }
	datas_disc[0] = 0;
	for(unsigned long long int i=1; i < *count; i++)
		{
			if(datas[i] >= datas[i-1]) datas_disc[i] = 0;
			else datas_disc[i] = 1;
		}
	return datas_disc;
}
