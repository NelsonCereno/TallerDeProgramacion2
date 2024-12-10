FLAGS = -g -Ofast -Wall

all: main

main: Graph.o State.o BranchAndBound.o main.o
	g++ ${FLAGS} Graph.o State.o BranchAndBound.o main.o -o main

Graph.o: Graph.h Graph.cpp
	g++ ${FLAGS} -c Graph.cpp

State.o: State.h State.cpp
	g++ ${FLAGS} -c State.cpp

BranchAndBound.o: BranchAndBound.h BranchAndBound.cpp
	g++ ${FLAGS} -c BranchAndBound.cpp

main.o: main.cpp
	g++ ${FLAGS} -c main.cpp

clean:
	rm -f *.o main