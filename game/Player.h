#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Monkey.h"
#include "Screen.h"


class Player: public Monkey
{
private:	
	int points;
public:
	Player(int _y, int _x, int _h = 6, int _w = 7);
	
	Screen HUD;
	Screen* MAPS;
	bool isAlive;
	int location;
	int fuelMax, fuel;

	void move();
	void spendFuel();
	void setHUD(Screen _HUD);
	void setMAPS(Screen* _MAPS);
	void jump(int _newLocation);
	bool intersects();
};

#endif // __PLAYER_H__
