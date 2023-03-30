all: test

test: test_graph.o graph.o
	g++ test_graph.o graph.o -o test

test_graph.o: test_graph.cpp
	g++ -c test_graph.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

clean:
	rm *.o test