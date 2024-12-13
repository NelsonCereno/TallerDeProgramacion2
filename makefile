FLAGS = -g -Ofast -Wall

all: main testGraph testState testBranchAndBound

main: Graph.o State.o BranchAndBound.o main.o
	g++ ${FLAGS} Graph.o State.o BranchAndBound.o main.o -o main

testGraph: Graph.o test_Graph.o
	g++ ${FLAGS} Graph.o test_Graph.o -o test_Graph

testState: Graph.o State.o test_State.o
	g++ ${FLAGS} Graph.o State.o test_State.o -o test_State

testBranchAndBound: Graph.o State.o BranchAndBound.o test_BranchAndBound.o
	g++ ${FLAGS} Graph.o State.o BranchAndBound.o test_BranchAndBound.o -o test_BranchAndBound

Graph.o: Graph.h Graph.cpp
	g++ ${FLAGS} -c Graph.cpp

State.o: State.h State.cpp
	g++ ${FLAGS} -c State.cpp

BranchAndBound.o: BranchAndBound.h BranchAndBound.cpp
	g++ ${FLAGS} -c BranchAndBound.cpp

main.o: main.cpp
	g++ ${FLAGS} -c main.cpp

test_Graph.o: test_Graph.cpp
	g++ ${FLAGS} -c test_Graph.cpp

test_State.o: test_State.cpp
	g++ ${FLAGS} -c test_State.cpp

test_BranchAndBound.o: test_BranchAndBound.cpp
	g++ ${FLAGS} -c test_BranchAndBound.cpp

clean:
	rm -f *.o main test_Graph test_State test_BranchAndBound