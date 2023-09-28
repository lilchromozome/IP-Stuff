# Some variable definitions to save typing later on
CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)


DataLoop.o: DataLoop.cpp DataLoop.h
	$(CC) -c DataLoop.cpp $(CFLAGS)

DataLoopTest:  DataLoopTest.o DataLoop.o
	$(CC) -o DataLoopTest DataLoop.o DataLoopTest.o 

DataLoopTest.o: DataLoopTest.cpp DataLoop.h
	$(CC) -c DataLoopTest.cpp $(CFLAGS)

test: DataLoopTest
	./DataLoopTest


TDataLoopTest:  TDataLoopTest.o
	$(CC) -o TDataLoopTest TDataLoopTest.o 

TDataLoopTest.o: TDataLoopTest.cpp TDataLoop.h TDataLoop.inc
	$(CC) -c TDataLoopTest.cpp $(CFLAGS)

ttest: TDataLoopTest
	./TDataLoopTest

clean:
	rm -f *.o hw3 test *~