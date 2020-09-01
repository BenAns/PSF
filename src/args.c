#include "args.h"

// File to implement subroutines to do with processing the arguments

args processArgs(int argc, char* argv[])
{
	//return (args){(uint64_t)1 << 24, (uint64_t)1 << 24, "primes.txt", 8};
	return (args) {(uint64_t)1 << 4, (uint64_t)1 << 4, "primes.txt", 4};
}