# 15puzzleMDbruteforce
Command line program in C that tries to find best NxN sliding puzzle based on MD sum

args:

size (for example 4 for 4x4 puzzle)

cap (for example 15 md sum for 4x4 puzzle)

max (for example 1000000 scrambles to check)


example:
smart.exe 4 15 1000000

compliation from source for fast search:
gcc fifteen.c -o smart -O3
