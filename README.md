# 15puzzleMDbruteforce
Command line program in C that tries to find best NxN sliding puzzle based on MD sum

args:

size (for example 4 for 4x4 puzzle) (size >= 2 ; size <= 30

cap (for example 15 md sum for 4x4 puzzle) (use big value at first to find the reasonable cap)

max (for example 1000000 scrambles to check) (it should go about 0.66s per million on 5x5 puzzle, a bit longer for bigger)


example:
smart.exe 4 15 1000000

compliation from source for fast search:
gcc fifteen.c mtwister.c -o smart -O3
