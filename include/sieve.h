#ifndef SIEVE
#define SIEVE

#include <stdlib.h>
#include <string.h>

#include "args.h"

// Header file to declare functions to do with the sieve calculations

typedef struct sieveData
{
	uint8_t* sieveMem;  // Memory to be used by the sieve
	uint64_t* storedPrimes;  // Previously found primes
	uint64_t sieveOffset;  // The number of times the sieveMem has been cleared and reused
	uint64_t primesFound;  // The number of primes found
} sieveData;

sieveData allocateSieve(args programArgs);
void deallocateSieve(sieveData sieve);
void iterateSieve(sieveData sieve, args programArgs);

void calculateSieve(args programArgs);
void fillOldPrimes(sieveData sieve, args programArgs);
void getNewPrimes(sieveData* sieve, args programArgs);
void resetStoredPrimes(sieveData sieve, args programArgs);

void appendNewPrimes(uint64_t* newPrimes, const char* filename);

#endif