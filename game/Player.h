#ifndef _PLAYER_H
#define _PLAYER_H

#include "Monkey.h"
#include "Screen.h"


class Player: public Monkey
{
private:
	int points;
	int fuel;
public:
	Player(int _y, int _x, int _h = 6, int _w = 8);
	
	Screen HUD;
	bool isAlive;

	void move();
	void spendFuel();
};

#endif // _PLAYER_H
