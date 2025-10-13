/*prototypes of the functions*/

/* the function FinalEpsilon takes as the input array of epsilons, maximal length of history, which type of normalization
is chosen and which rank , where
normalizationType == 1 => exponential normalization of the form (normalizationRank)^i
normalizationType == 2 => polynomial normalization of the form (i*i * ... * i) where
multiplication is taken normalizationRank  times
return value : final epsilon or -1 if wrong arguments are fed to the function
*/

long double FinalEpsilon(long double  *epsilons, int maxHistoryLength, int normalizationType,int normalizationRank);
