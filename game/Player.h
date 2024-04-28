#ifndef _PLAYER_H
#define _PLAYER_H

#include "Monkey.h"

class Player: public Monkey
{
private:
	int points;
	int fuel;
public:
	Player(int _y, int _x, int _h = 0, int _w = 7);

	void move();	
};

#endif // _PLAYER_H
