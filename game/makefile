all: main

main: main.o
	g++ -lncurses main.o -o game

main.o: main.cpp
	g++ -lncurses -g -c  main.cpp -o main.o

clean:
	rm -r *.o
	rm game
