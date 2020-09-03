#include "fileOps.h"

// File to implement subroutiunes to do with file operations

// Clears the contents of a file
void clearFile(const char* filename)
{
	fclose(openFileSafe(filename, "wb"));
}

// Append a new primes to the end of a file
void appendNewPrimes(uint64_t* newPrimes, uint64_t numNewPrimes, const char* filename)
{
	FILE* file = openFileSafe(filename, "ab");
	fwrite(newPrimes, sizeof(uint64_t), numNewPrimes, file);
	fclose(file);
}

// Changes the current primes stored in memory
void changeStoredPrimes(uint64_t* storedPrimes, uint64_t offset, uint64_t memPrimes, const char* filename)
{
	memset(storedPrimes, 0, memPrimes);

	FILE* file = openFileSafe(filename, "r");
	fseek(file, (long)(offset * memPrimes), SEEK_SET);
	fread(storedPrimes, memPrimes, 1, file);
	fclose(file);
}

// Opens a file safely
FILE* openFileSafe(const char* filename, const char* mode)
{
	FILE* file;
	errno_t err = fopen_s(&file, filename, mode);
	
	if(err != 0)
	{
		printf("Error: Unable to open file %s for writing\n", filename);
		exit(-1);
	}

	return file;
}