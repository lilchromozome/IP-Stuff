CC = gcc
CFLAGS = -g -std=c11 -Wall -Wextra -pedantic

CXX = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CXXFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)
	

%.o : %.c
	$(CC) $(CFLAGS) -c $*.c -o $*.o

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $*.cpp -o $*.o

C_SRCS = pnglite.c
CXX_SRCS = main.cpp plot.cpp bounds.cpp image.cpp exception.cpp \
	reader.cpp renderer.cpp expr.cpp expr_parser.cpp func.cpp \
	fill.cpp

OBJS = $(C_SRCS:.c=.o) $(CXX_SRCS:.cpp=.o)

plot : $(OBJS)
	$(CXX) -o $@ $(OBJS) -lm -lz

clean :
	rm -f *.o plot

depend :
	$(CC) -M $(CFLAGS) $(C_SRCS) > depend.mak
	$(CXX) -M $(CXXFLAGS) $(CXX_SRCS) >> depend.mak

depend.mak :
	touch $@

include depend.mak

exception.o: exception.cpp exception.h
	$(CXX) -c exception.cpp

func.o: func.cpp func.h
	$(CXX) -c func.cpp $(CXXFLAGS)
expr.o: expr.cpp expr.h
	$(CXX) -c expr.cpp $(CXXFLAGS)

expr_parser.o: expr_parser.cpp expr_parser.h expr.h
	$(CXX) -c expr_parser.cpp $(CXXFLAGS)

expr_test: expr_test.o expr.o expr_parser.o func.o exception.o
	$(CXX) -o expr_test expr.o expr_test.o expr_parser.o func.o exception.o

expr_test.o: expr_test.cpp expr.h
	$(CXX) -c expr_test.cpp $(CXXFLAGS)

test: expr_test
	./expr_test