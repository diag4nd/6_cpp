all: main

clean:
	rm -rf game *.o game

main: main.o functions.o globals.o Monkey.o Screen.o Player.o Banana.o Fuel.o
	g++ -lpanel -lncurses main.o -o game
	./game

main.o: main.cpp
	g++ -lpanel -lncurses -c  main.cpp -o main.o

Monkey.o: Monkey.cpp
	g++ -lpanel -lncurses -c  Monkey.cpp -o Monkey.o

Screen.o: Screen.cpp
	g++ -lpanel -lncurses -c  Screen.cpp -o Screen.o

Player.o: Player.cpp
	g++ -lpanel -lncurses -c  Player.cpp -o Player.o

Banana.o: Banana.cpp
	g++ -lpanel -lncurses -c  Banana.cpp -o Banana.o

Fuel.o: Fuel.cpp
	g++ -lpanel -lncurses -c  Fuel.cpp -o Fuel.o

globals.o: globals.cpp
	g++ -lpanel -lncurses -c  globals.cpp -o globals.o

functions.o: functions.cpp
	g++ -lpanel -lncurses -c  functions.cpp -o functions.o

