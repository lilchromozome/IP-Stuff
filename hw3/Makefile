# Homework 3
GCC = gcc
CONSERVATIVE_FLAGS = -std=c99 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

hw3: hw3.o functions.o
	$(GCC) -o hw3 hw3.o functions.o

hw3.o: hw3.c functions.h
	$(GCC) -c hw3.c $(CFLAGS)

# TODO: instructions to compile and run the test file

test_functions:  test_functions.o functions.o
	$(GCC) -o test_functions test_functions.o functions.o 

test_functions.o: test_functions.c functions.h
	$(GCC) -c test_functions.c $(CFLAGS)

test: test_functions
	./test_functions

clean:
	rm -f *.o hw3 test *~
