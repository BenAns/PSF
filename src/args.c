#include "args.h"

// File to define constants and subroutines to do with processing the arguments

const char* helpScreen =
"Argument Form: ./psf [[Argument Type] [Argument Value]]\n"
"Multipliers: [num]K, [num]M or [num]G act as multipliers for 2**10, 2**20 and 2**30  for [num] respectively\n"
"Arguments:\n"
"-help: Opens this help screen, does not run the sieve,. written alone with no other arguments\n"
"-sieveSize: Size of memory to be used for the sieve, default = 1M\n"
"-primesSize: Size of memory to be used for primes, default = 1M\n"
"-fileWriteSize: Maximum amount of memory of new primes to store at once before writing to the file, 1M\n"
"-filename: Name of file to store found primes in, default = primes.bin\n"
"-sieveIterations: Numbers of iterations (to fill the sieve memory each time) to be performed, default = 0 (unlimited)\n";

// Processes the arguments given to the program
args processArgs(int argc, char* argv[])
{
	// Sets default arguments
	args progArgs = (args){(uint64_t)1 << 20, ((uint64_t)1 << 20) / sizeof(uint64_t), ((uint64_t)1 << 20) / sizeof(uint64_t), "primes.bin", 0};

	// Checks if the help screen was requested
	if(argc == 2 && !strcmp("-help", argv[1]))
	{
		printHelp(NULL, NULL);
	}

	checkValidArgs(argc, argv);
	parseArgs(argc, argv, &progArgs);

	return progArgs;
}

// Makes sure the arguments given to the program are valid
void checkValidArgs(int argc, char* argv[])
{
	// Makes sure there is a valid number of arguments
	if(argc % 2 == 0)
	{
		printHelp("Error: Invalid number of aruments", NULL);
	}
}

// Goes through and parses the given arguments to the program
void parseArgs(int argc, char* argv[], args* progArgs)
{
	for(int i = 1; i < argc; i += 2)
	{
		parseArgPair(argv[i], argv[i + 1], progArgs);
	}
}

// Parses one argument type/value pair
void parseArgPair(char* argType, char* argVal, args* progArgs)
{
	// Deals with string arguments
	if(!strcmp(argType, "-filename"))
	{
		progArgs->filename = argVal;
		return;
	}

	// Deals with integer arguments
	uint64_t argSize = getArgSize(argVal);
	if(!strcmp(argType, "-sieveSize"))
	{
		progArgs->sieveSize = argSize;
	}
	else if(!strcmp(argType, "-primesSize"))
	{
		progArgs->memPrimes= argSize / sizeof(uint64_t);
	}
	else if(!strcmp(argType, "-fileWriteSize"))
	{
		progArgs->fileWritePrimes = argSize / sizeof(uint64_t);
	}
	else if(!strcmp(argType, "-sieveIterations"))
	{
		progArgs->sieveIterations = argSize;
	}
	else
	{
		printHelp("Error: Invalid argument name: ", argType);
	}
}

// Parses an integer argument value
uint64_t getArgSize(char* argVal)
{
	uint64_t multiplier = getMultiplier(argVal);

	size_t len = strlen(argVal);
	char* lastChar = NULL;
	uint64_t argSize = strtoull(argVal, &lastChar, 10);

	if(argSize == 0 || argSize == ULLONG_MAX || (multiplier == 1 && lastChar != argVal + len) || (multiplier != 1 && lastChar != argVal + len - 1))
	{
		printHelp("Invalid integer argument (not an integer or not in the valid range): ", argVal);
	}

	return argSize * multiplier;
}

// Parses the multiplier from an integer argument value
uint64_t getMultiplier(char* argVal)
{
	// Gets the multiplier character
	size_t len = strlen(argVal);
	char finalChar = argVal[len - 1];
	
	// Gets the multiplier value
	if(finalChar >= '0' && finalChar <= '9')
	{
		return (uint64_t)1;
	}
	else if(finalChar == 'k' || finalChar == 'K')
	{
		return (uint64_t)1 << 10;
	}
	else if(finalChar == 'm' || finalChar == 'M')
	{
		return (uint64_t)1 << 20;
	}
	else if(finalChar == 'g' || finalChar == 'G')
	{
		return (uint64_t)1 << 30;
	}
	else
	{
		printHelp("Invalid integer size argument value: ", argVal);
		return 0;  // Should never return here
	}
}

// Prints the help screen (and with an error message if needed)
void printHelp(const char* errorInfo, const char* errorArg)
{
	printf("%s%s%s%s", errorInfo ? errorInfo: "", errorArg ? errorArg: "", errorInfo? "\n" : "", helpScreen);
	exit(0);
}