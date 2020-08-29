project(PSF)
cmake_minimum_required(VERSION 3.0)

add_executable(GTMLUnitTests src/main.c src/sieve.c src/args.c)
target_include_directories(GTMLUnitTests PRIVATE include)