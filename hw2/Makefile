Makefile: 
CC=gcc
CFLAGS = -std=99 -pedantic -Wall -Wextra

main: hw2_1.o           
	$(CC) -o main hw2_1.o	

hw2_1.o: hw2_1.c 
	$(CC) $(CFLAGS) -c hw2_1.c 

clean:
	rm -f *.o main
