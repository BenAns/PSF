#ifndef ARGS
#define ARGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>

// Header file to declare subroutines and constants to do with processing the program arguments

typedef struct ARGS
{
	uint64_t sieveSize;  // Size in bytes of memory to be used for the sieve
	uint64_t memPrimes;  // Numbers of primes to be stored at a time in memory
	uint64_t fileWritePrimes;  // How many new primes to store at once before writing to the file
	const char* filename;  // Name of file to store found primes in
	uint64_t sieveIterations;  // Numbers of iterations (to fill the sieve memory each time) to be performed
} args;

extern const char* helpscreen;

args processArgs(int argc, char* argv[]);

void checkValidArgs(int argc, char* argv[]);
void parseArgs(int argc, char* argv[], args* progArgs);
void parseArgPair(char* argType, char* argVal, args* progArgs);
uint64_t getArgSize(char* argVal);
uint64_t getMultiplier(char* argVal);
void printHelp(const char* errorInfo, const char* errorArg); 

#endif