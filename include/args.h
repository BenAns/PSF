#ifndef ARGS
#define ARGS

#include <inttypes.h>

// Header file to declare subroutines to do with processing the arguments

typedef struct ARGS
{
	uint64_t sieveSize;  // Size in bytes of memory to be used for the sieve
	uint64_t memPrimes;  // Numbers of primes to be stored at a time in memory
	const char* filename;  // Name of file to store found primes in
	uint64_t sieveIterations;  // Numbers of iterations (to fill the sieve memory each time) to be performed
} args;

args processArgs(int argc, char* argv[]);

#endif