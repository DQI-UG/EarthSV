#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "constants.h"
	/* the function FinalEpsilon takes as the input array of epsilons, maximal length of history, which type of normalization is chosen
	and which rank where
        normalizationType == 1 => exponential normalization of the form (normalizationRank)^i
	and normalizationType ==2 => polynomial normalization  of the form (i * i ... * i ) where multiplication is taken normalizationRank times
	return value : final epsilon or -1 if wrong arguments are fed to the function
*/
long double FinalEpsilon(long double  *epsilons, int maxHistoryLength, int normalizationType, int normalizationRank){
long double finalEpsilon=0;
long double Weight=0;
long double power;
int element;
int i,j;
if (normalizationType==1){ // powertype normalization
	for(i=0;i<=maxHistoryLength; i++){
		power=powl((long double )normalizationRank,(long double )i);
		Weight = Weight+1/power;
		if(i<=number_of_bytes){
		finalEpsilon = finalEpsilon +  epsilons[i]/power;
		}
		else finalEpsilon = finalEpsilon +  0.5/power;
	}
finalEpsilon =finalEpsilon/Weight;
}

if (normalizationType==2 && normalizationRank>0){//square and higher powers normalization
	for(i=0;i<=maxHistoryLength; i++){
		element=1;
		for(j=1;j<=normalizationRank; j++){ element = element*(i+1);} // changed to (i+1)^normalizationRank
		Weight = Weight+1/((long double)element);
		finalEpsilon = finalEpsilon +  epsilons[i]/((long double)element);
	}
finalEpsilon =finalEpsilon/Weight;
}

if (((normalizationType  != 2) && (normalizationType !=1) ) || normalizationRank <=0)
finalEpsilon = -1; //return an error value if the inputs are wrong


return finalEpsilon;
}

