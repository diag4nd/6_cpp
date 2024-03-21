all: main

main: task2.o IntGraph.o
	g++ task2.o IntGraph.o -o Graphs

task2.o: task2.cpp
	g++ -c task2.cpp

IntGraph.o: IntGraph.cpp
	g++ -c IntGraph.cpp

clean:
	rm *.o
