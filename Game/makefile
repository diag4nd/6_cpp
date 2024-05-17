all: main

clean:
	rm -rf game *.o game

main: main.o functions.o globals.o Monkey.o Screen.o Player.o Object.o 
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

Enemy.o: Object.cpp
	g++ -lpanel -lncurses -c  Object.cpp -o Object.o

globals.o: globals.cpp
	g++ -lpanel -lncurses -c  globals.cpp -o globals.o

functions.o: functions.cpp
	g++ -lpanel -lncurses -c  functions.cpp -o functions.o

