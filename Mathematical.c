#include "Mathematical.h"

#include <stdlib.h>
#include <math.h>

/*** FUNCTION DEFINITIONS ***/

int maxIndex(int* datas, int count)
{
	int i = 0;
	int max = datas[0];
	int maxIndex = 0;

	for(i=0; i < count; i++)
	{
		if(datas[i] > max)
		{
			max = datas[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}


long double maxLongDouble(long double* datas, int count)
{
	long double max = 0;

	for(int i=0; i < count; i++)
	{
		if(datas[i] > max)
		{
			max = datas[i];
		}
	}
	return max;
}
