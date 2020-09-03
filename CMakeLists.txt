project(PSF)
cmake_minimum_required(VERSION 3.0)

add_executable(psf src/main.c src/sieve.c src/args.c src/fileOps.c)
target_include_directories(psf PRIVATE include)