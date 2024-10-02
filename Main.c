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
#include "TextIO.h"
#include "FinalEpsilon.h"
//#include "argpProgram.h"

const char *argp_program_version = "SVEarth 1.0";
const char *argp_program_bug_address = "<maciej.stankiewicz@ug.edu.pl>";
int info=0;
int debug=0;
unsigned long long int numberOfLines =0;
unsigned long long int sourceLength = 0;
unsigned long long int number_of_bytes = 0;

struct arguments
{
char *argz;
size_t argz_len;
int historyLength;
unsigned int disc_method;
unsigned int method_of_epsilon;
unsigned long long int number_of_lines;
};

/* Program documentation. */
static char doc[] = "SVEarth program.\n\n Here will be short discription of the program.\n\n Program can be run with the following options ";

/* A description of the arguments we accept. */
static char args_doc[] = "PATH TO ASCII DATA FILE";

static int parse_opt (int key, char *arg,struct argp_state *state)
{
    unsigned char *data = NULL;
	unsigned char *discretizedData = NULL;
    long double *earthDatas = NULL;
    unsigned long long int number_of_bytes = 0;
	long double *epsilons = NULL;
	unsigned long long int sourceLength = 0;
    int max_num_of_arg = 5;
    struct arguments *a = state->input;
    int historyLength = a->historyLength;
    long double finalEpsilon;
    int HistoryLength (unsigned long long int n)
    {
    int hl =(int)(floorf((float)logl((long double)n)/logl(2))) -1;
    return hl;
    }
    switch (key)
    {
    case 'i':
    {
        info=1;
        debug=1;
        break;
    } 
    case 'l':
    {
        if (arg == NULL) a->historyLength = MAXHISTORY;
        else a->historyLength = atoi(arg);
    break;
    }
    case 'n':
    {
    if (arg == NULL) a->number_of_lines = 0;
    else
        a->number_of_lines = atoi(arg);
    break;
    }
    case 'e':
    {
    if (arg == NULL) a->method_of_epsilon = METHOD_OF_EPSILON;
    else if (atoi(arg)==1||atoi(arg)==2||atoi(arg)==3||atoi(arg)==4)
        a->method_of_epsilon = atoi(arg);
    else a->method_of_epsilon = METHOD_OF_EPSILON;
        //epsilons = calculateEpsilons(data, sourceLength, historyLength);//main calculation of frequencies and epsilons
//epsilons = calculateEpsilons(data, sourceLength, HistoryLength(sourceLength));//main calculation of frequencies and epsilons
    break;
    }
    case 'd':
    {
    if (arg == NULL) a->disc_method = DISC_METHOD;
    else if (atoi(arg)==1||atoi(arg)==2||atoi(arg)==3||atoi(arg)==4||atoi(arg)==5)
        a->disc_method = atoi(arg);
    else a->disc_method = DISC_METHOD;
    break;
    }
    case ARGP_KEY_ARG:
    {
    //size_t count = argz_count (a->argz, a->argz_len);
    argz_add(&a->argz, &a->argz_len, arg);
    if (info)
		printf("INFO: Verbose version\n");
    if (info)
		printf("INFO: Data file: %s\n", a->argz);
    if (info)
		printf("INFO: Counting file lines\n");
    sourceLength = countData(a->argz);
    printf("\nThe number of lines in the file %lld\n", sourceLength);
    if ((a->number_of_lines == 0 || a->number_of_lines > sourceLength))
    {
        numberOfLines = sourceLength;
    }
    else
    {
        numberOfLines = a->number_of_lines;
    }
    number_of_bytes = numberOfLines;
    if (info)
        printf("INFO: File lines = %lld\n", sourceLength);
    if (info) printf("INFO: Loading data from file\n");
	earthDatas = loadData(a->argz, &number_of_bytes);//loading data from file
	if (info)printf("INFO: Data loaded\n");
    if (info) printf("INFO: Using history of length %d\n", a->historyLength);
    if (info) printf("INFO: The chosen method of counting epsilon is %d.\n", a->method_of_epsilon);
    if (info) printf("INFO: Program takes %lld lines from data file.\n",number_of_bytes);
    //The choice of discretization method
    if(a->disc_method ==1){
        if (info) printf("INFO: The chosen discretization method is %d.\n", a->disc_method);
        discretizedData = discretization1(earthDatas, &number_of_bytes,0);
    }
    else if(a->disc_method ==2){
        if (info) printf("INFO: The chosen discretization method is %d.\n", a->disc_method);
        discretizedData = discretization2(earthDatas, &number_of_bytes,
			0);		
    }
    else if(a->disc_method ==3){
        if (info) printf("INFO: The chosen discretization method is %d.\n", a->disc_method);
        discretizedData = discretization3(earthDatas, &number_of_bytes,
			0);		
    }
    else if(a->disc_method ==4){
        if (info) printf("INFO: The chosen discretization method is %d.\n", a->disc_method);
        discretizedData = discretization4(earthDatas, &number_of_bytes,
			0);		
    }
    else if(a->disc_method ==5){
        if (info) printf("INFO: The chosen discretization method is %d.\n", a->disc_method);
        discretizedData = discretization5(earthDatas, &number_of_bytes,
			0);
    }
	//if (DEBUG)
	//	printf("DEBUG: medicalDatasDiscretized=%lld\n", number_of_bytes);
	//datas = minMaxPreprocessing(medicalDatasDiscretized, &number_of_bytes, 3, 3);//use this for "cut out trends" subroutine
	//if (DEBUG)
	//	printf("DEBUG: \nnmedicalDatasDiscretized2=%lld\n", number_of_bytes);
	data = discretizedData;		//no "cut out trends" subroutine
	//sourceLength = number_of_bytes;
	if (debug)
		printf("DEBUG: Source length %lld %lld\n", sourceLength,
				number_of_bytes);
	if (debug)
		printf("DEBUG: File loaded\n");
	epsilons = calculateEpsilons(data, sourceLength, historyLength);//main calculation of frequencies and epsilons
	//printEpsilons(historyLength, sourceLength, epsilons); //printing epsilons
	printEpsilons(historyLength, sourceLength, epsilons); //printing epsilons
    if( a->method_of_epsilon==1){
        finalEpsilon = FinalEpsilon(epsilons, HistoryLength(sourceLength),1,2);
        if (finalEpsilon < 0) printf("The function FinalEpsilon invoked with  wrong parameters");
        if (info) printf("Final epsilon based on powers for history length %d %.15Lf\n ",HistoryLength(sourceLength),finalEpsilon);  
    }
    else if(a->method_of_epsilon==2){
        finalEpsilon =FinalEpsilon(epsilons,HistoryLength(sourceLength),2,2);
		if (info) printf("Final epsilon based on squares %.15Lf\n",finalEpsilon);
    }
    else if(a->method_of_epsilon==3){
        finalEpsilon =FinalEpsilon(epsilons,HistoryLength(sourceLength),2,1);
		if (info) printf("Final epsilon based on linear new method %.15Lf\n",finalEpsilon);
    
    }
	else if(a->method_of_epsilon==4){
        finalEpsilon =FinalEpsilon(epsilons,HistoryLength(sourceLength),2,3);
		if (info) printf("Final epsilon based on triple power %.15Lf\n",finalEpsilon);
    }
    break;
    }
    case ARGP_KEY_INIT:
    {
    a->argz = 0;
    a->argz_len = 0;
    a->historyLength = MAXHISTORY;
    a->disc_method = DISC_METHOD;
    a->method_of_epsilon = METHOD_OF_EPSILON;
    a->number_of_lines = number_of_bytes;
    break;
    }
    case ARGP_KEY_END:
    {
    size_t count = argz_count (a->argz, a->argz_len);
    if (count > max_num_of_arg)
    argp_failure (state, 1, 0, "Too many arguments.Use --help option for more details.");
    else if (count <1)
    argp_failure (state, 1, 0, "Too few arguments. You need to add path to data file. Use --help option for more details.");
    break;
}
default:
    return ARGP_ERR_UNKNOWN;
}
free(data);
free(epsilons);
return 0;
}

/*** PROTOTYPES ***/

//int mainSV(int argc, char *argv[]);
int HistoryLength (unsigned long long int n){
int hl =(int)(floorf((float)logl((long double)n)/logl(2))) -1;
return hl;
}

/*** MAIN ***/
//int main(int argc, char *argv) {
int main(int argc, char **argv) {
	//if (argc == 1)
	//	displayHelp(); //If no argument was passed display help info

	clock_t startTime = clock();

	//mainSV(argc, argv); //main function for SV estimation

	
	struct argp_option options[] =
    {
    { "historyLength", 'l',"NUM", OPTION_ARG_OPTIONAL, "Set history length. The default history length is  20."},
    { "numLines", 'n',"NUM", OPTION_ARG_OPTIONAL, "Set the number of lines taken from the data file. The default is all of the lines from the data file."},
    { "methodEpsilon",'e', "NUM", OPTION_ARG_OPTIONAL, "Set the method of counting epsilon. The default method is 1."},
    { "dscr", 'd',"NUM", OPTION_ARG_OPTIONAL, "Set the discretization method.The default method is 2."},
    { "info", 'i',0,0, "Additional information appearing during running of the program."},
    { 0 }
    };
//int arg_count = 1;//minimal number of arguments
struct argp argp = {options,parse_opt,args_doc,
 doc};
struct arguments arguments;
if (argp_parse (&argp, argc, argv, 0, 0, &arguments) == 0)
{
const char *prev = NULL;
char *word;
while ((word = argz_next (arguments.argz, arguments.argz_len, prev)))
{
printf (" %s", word);
prev = word;
}
printf ("\n");
free (arguments.argz);
};
clock_t endTime = clock();
double runningTime = (double) (endTime - startTime) / CLOCKS_PER_SEC;
if (info) printf("\nINFO: Program running time was %lf seconds\n", runningTime);
return 0;
// return argp_parse (&argp, argc, argv, 0, 0, &arg_count);
}

//int mainSV(int argc, char *argv[]) {
	
	

	//const unsigned long long int eventsWFLength = 284282034;
	//const unsigned long long int eventsSWFLength = 520407646;

	//number_of_bytes = count_earth_dataNoise(argv[1]);//automatic counting
	//number_of_bytes = eventsSWFLength;  //manual entry
	

//	return 0;
//}