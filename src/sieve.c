#include "sieve.h"

// File to implement subroutines to do with sieve calculations

// Calculates the sieve processes from a high level
void calculateSieve(args programArgs)
{
	sieveData sieve = allocateSieve(programArgs);
	iterateSieve(sieve, programArgs);
	deallocateSieve(sieve);
}

// Allocates the sieve according to the arguments provided by the user
sieveData allocateSieve(args programArgs)
{
	sieveData sieve;
	sieve.sieveMem = calloc(programArgs.sieveSize, 1);
	sieve.storedPrimes = calloc(programArgs.memPrimes, 1);
	sieve.sieveOffset = 0;
	sieve.primesFound = 0;

	return sieve;
}

// Deallocated the sieve
void deallocateSieve(sieveData sieve)
{
	free(sieve.sieveMem);
	free(sieve.storedPrimes);
}

// Performs iterations to calculate new primes with the sieve with the number of times the user specified
void iterateSieve(sieveData sieve, args programArgs)
{
	for(uint64_t i = 0; i < programArgs.sieveIterations || programArgs.sieveIterations == 0; i++)
	{
		// Performs the current iteration of the table
		fillOldPrimes(sieve, programArgs);
		getNewPrimes(&sieve, programArgs);

		// Clears for the next iteration of the table
		resetStoredPrimes(sieve, programArgs);
		memset(sieve.sieveMem, 0, programArgs.sieveSize);
		sieve.sieveOffset++;
	}
}