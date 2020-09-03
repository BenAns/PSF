#ifndef FILEOPS
#define FILEOPS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

// Header file to declare subroutines to do with file operations

void clearFile(const char* filename);
void appendNewPrimes(uint64_t* newPrimes, uint64_t numNewPrimes, const char* filename);
void changeStoredPrimes(uint64_t* storedPrimes, uint64_t offset, uint64_t memPrimes, const char* filename);

FILE* openFileSafe(const char* filename, const char* mode);

#endif