#include "args.h"
#include "sieve.h"

// Main file, calls argument processing and the sieve calculations

int main(int argc, char* argv[])
{
	args programArgs = processArgs(argc, argv);
	calculateSieve(programArgs);

	return 0;
}