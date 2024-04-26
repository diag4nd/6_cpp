all: main

main: main.o
	g++ -lpanel -lncurses main.o -o game

main.o: main.cpp
	g++ -lpanel -lncurses -g -c  main.cpp -o main.o

clean:
	rm -r *.o
	rm game
