#include <stdio.h>
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
		memset(sieve.sieveMem, 0, programArgs.sieveSize);
		sieve.sieveOffset++;
	}
}

// Marks blank sieve memory with multiples of already-found primes
void fillOldPrimes(sieveData sieve, args programArgs)
{
	uint64_t startIndex = sieve.sieveOffset * programArgs.sieveSize * 8;  // The first number in the current iteration of the sieve

	// Goes through each prime and marks corresponding numbers in the sieve
	for(uint64_t i = 0; i < sieve.primesFound; i++)
	{
		uint64_t firstMarked = (sieve.storedPrimes[i] - (startIndex % sieve.storedPrimes[i])) % sieve.storedPrimes[i];
		for(uint64_t j = firstMarked; j < programArgs.sieveSize * 8; j++)
		{
			markNonPrimes(sieve, programArgs, sieve.storedPrimes[i], j);
		}
	}
}

// Marks multiples of a specific prime in the current sieve from a given offset
void markNonPrimes(sieveData sieve, args programArgs, uint64_t newPrime, uint64_t firstIndex)
{
	for(uint64_t i = firstIndex; i < programArgs.sieveSize * 8; i += newPrime)
	{
		// Marks the current number as non-prime
		sieve.sieveMem[i / 8] |= (uint64_t)1 << i % 8;
	}
}

// Gets new primes from the current sieve iteration
void getNewPrimes(sieveData* sieve, args programArgs)
{
	// Goes through each number in the sieve and finds primes
	for(uint64_t i = 0; i < programArgs.sieveSize; i++)
	{
		if(sieve->sieveMem[i] != 0xff)
		{
			processNewPrimes(sieve, programArgs, i);
		}
	}
}

// Processes a new prime/new primes found in the sieve
void processNewPrimes(sieveData* sieve, args programArgs, uint64_t sieveIndex)
{
	uint8_t newPrimes = sieve->sieveMem[sieveIndex];
	uint64_t currentNum = (programArgs.sieveSize * sieve->sieveOffset + sieveIndex) * 8;

	// Goes through each of the possible numbers in the byte that may be a new prime
	for(uint8_t i = 0; i < 8; i++)
	{
		// Updates the known primes when a new prime is found
		if((newPrimes & (uint8_t)1 << i) == 0 && currentNum > 1)
		{
			sieve->storedPrimes[sieve->primesFound++] = currentNum;
			markNonPrimes(*sieve, programArgs, currentNum, currentNum - programArgs.sieveSize * sieve->sieveOffset * 8);
			appendNewPrime(currentNum, programArgs.filename);
			newPrimes = sieve->sieveMem[sieveIndex];
		}

		currentNum++;
	}
}

// Appends a new prime to the end of a file
void appendNewPrime(uint64_t newPrime, const char* filename)
{
	FILE* file;
	errno_t err = fopen_s(&file, filename, "ab");
	if(err != 0)
	{
		printf("Error: Unable to open file %s for writing\n", filename);
		exit(-1);
	}
	fwrite(&newPrime, sizeof(uint64_t), 1, file);
	fclose(file);
}