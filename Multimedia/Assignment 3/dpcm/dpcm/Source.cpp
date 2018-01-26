#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "SDL.h"

struct {
	int *data;
	int size;
	bool encodeMode;
	int *resultSet;
} prog;

bool checkUsage(int argc, char *argv[]);			
void fillData(char *argv[]);			
void encode();					
int quantize(int e);				
void decode();									

// Returns as 1 for any misuse of command-line arguments
bool checkUsage(int argc, char *argv[])
{
	// User called for help or enter wrong argument
	if (argc == 2 && !(strcmp(argv[1], "-h"))) {
		printf("\nUsage:\tdpcm –[h|e|d] n1 n2 n3 ...\n\n-e encoding data\n-d decoding data\n-h help\n\n");
		printf("Follow -e or -d with an array of values as such \nExample:\tdpcm -e 130 150 140 200 230 \n"); 
		return false;
	}

	// Incorrect number of argument 
	else if (argc < 3) {
		printf("Usage:\tdpcm –[h|e|d] n1 n2 n3 ...\n");
		printf("Example:\tdpcm -e 130 150 140 200 230 \n"); 
		return false;
	}

	// Entered correct function and correct number of argument, check for which function user is calling 
	else if (!(strcmp(argv[1], "-e"))) {
		prog.encodeMode = true;
		prog.size = argc - 2;
		return true;
	}
	else if (!(strcmp(argv[1], "-d"))) {
		prog.encodeMode = false;
		prog.size = argc - 2;
		return true;
	}
	else {
		printf("Usage:\tdpcm –[h|e|d] n1 n2 n3 ...\n");
		return false;
	}
}

// Store command-line arguments in storage buffer
void fillData(char *argv[])
{
	int j = 2, convertedArgument = 0;	
	for (int i = 0; i < prog.size; i++, j++)
	{
		char *argument = argv[j];
		if (argument[0] == '-') {		
			convertedArgument = atoi(++argument);
			convertedArgument = convertedArgument * -1;
		}
		else {
			convertedArgument = atoi(argument);	
		}

	
		if (convertedArgument > 255 && prog.encodeMode == true)			//encoding needs to be between 0 and 255
			convertedArgument = 255;
		else if (convertedArgument < 0 && prog.encodeMode == true)
			convertedArgument = 0;

		prog.data[i] = convertedArgument;
	}
}

void encode()
{
	int encodeCount = 0;
	int f_tilde_OneAgo = prog.data[encodeCount];	
	int f_tilde_TwoAgo = prog.data[encodeCount];

	prog.resultSet[encodeCount] = prog.data[encodeCount];	

	for (encodeCount = 1; encodeCount < prog.size; encodeCount++)	
	{	
		int f = ((f_tilde_OneAgo + f_tilde_TwoAgo)/2);	// f = truncation ((fn-1 + fn-2)/2)
		int e = prog.data[encodeCount] - f;			// e = fn - f
		int e_tilde = quantize(e);				// Quantaization 

		prog.resultSet[encodeCount] = e_tilde;			

		f_tilde_TwoAgo = f_tilde_OneAgo;			// Shift f_tilde(n-2) and f_tilde(n-1) forward
		f_tilde_OneAgo = f + e_tilde;
	}
}

// Quantize the value e and return e_tilde
int quantize(int e)
{
	return 16 * ((255 + e)/16) - 256 + 8;			
}

void decode()
{
	int decodeCount = 0;
	int f_tilde_OneAgo = prog.data[decodeCount];	
	int f_tilde_TwoAgo = prog.data[decodeCount];

	prog.resultSet[decodeCount] = prog.data[decodeCount];	

	for (decodeCount = 1; decodeCount < prog.size; decodeCount++)	
	{
		int e_tilde = prog.data[decodeCount];	

		prog.resultSet[decodeCount] = e_tilde + ((f_tilde_OneAgo + f_tilde_TwoAgo) / 2); 	// 	e tilde is provided by user, calculate f by using formula: f = truncation ((fn-1 + fn-2)/2)

		if (prog.resultSet[decodeCount] > 255)
			prog.resultSet[decodeCount] = 255;
		else if (prog.resultSet[decodeCount] < 0)
			prog.resultSet[decodeCount] = 0;

		f_tilde_TwoAgo = f_tilde_OneAgo;
		f_tilde_OneAgo = prog.resultSet[decodeCount];
	}
}

int main(int argc, char *argv[])
{
	double SQNR ; 

	SQNR = 6.02 * 8 + 1.76;

	if ((checkUsage(argc, argv)) == false )	
		return 1;

	prog.data = (int *)malloc(sizeof(int) * (prog.size));
	prog.resultSet = (int *)malloc(sizeof(int) * (prog.size));

	fillData(argv);			
	
	if (prog.encodeMode == true)	
		encode();
	else
		decode();

	if (prog.encodeMode == true)
		printf("\nEncoding output: ");
	else
		printf("\nDecoding output: ");

	for (int i = 0; i < prog.size; i++)
	{
		printf(" %d", prog.resultSet[i]);
	}
	printf("\nSNR: %g (dB)\n", SQNR);

	return 0;
}