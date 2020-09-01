#ifndef SIEVE
#define SIEVE

#include <stdlib.h>
#include <string.h>

#include "args.h"
#include "fileOps.h"

// Header file to declare functions to do with the sieve calculations

typedef struct sieveData
{
	uint8_t* sieveMem;  // Memory to be used by the sieve
	uint64_t* storedPrimes;  // Previously found primes
	uint64_t* primesToWrite;  // The primes to write to the file
	uint64_t sieveOffset;  // The number of times the sieveMem has been cleared and reused
	uint64_t primesFound;  // The number of primes found
	uint64_t numNewPrimes;  // The number of new primes found in the current iteration
} sieveData;

sieveData allocateSieve(args programArgs);
void deallocateSieve(sieveData sieve);
void iterateSieve(sieveData sieve, args programArgs);

void calculateSieve(args programArgs);
void fillOldPrimes(sieveData sieve, args programArgs);
void getNewPrimes(sieveData* sieve, args programArgs);

void markNonPrimes(sieveData sieve, args programArgs, uint64_t newPrime, uint64_t firstIndex);
void processNewPrimes(sieveData* sieve, args programArgs, uint64_t sieveIndex);

#endif