#ifndef __PLAYER_H__
#define __PLAYER_H__

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
	Screen* MAPS;
	bool isAlive;
	int location;

	void move();
	void spendFuel();
	void setHUD(Screen _HUD);
	void setMAPS(Screen* _MAPS);
	void jump(int _newLocation);
};

#endif // __PLAYER_H__
