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
	
	Screen TITLE;
	Screen* MENU;
	Screen HUD;
	Screen* MAPS;
	Screen* END;

	int choice;
	bool isAlive;
	int location;
	int fuelMax, fuel;
	int menuLen, mapsLen;
	int endLen;

	void move();
	void spendFuel();
	void setHUD(Screen _HUD);
	void setMAPS(Screen* _MAPS);
	void jump(int _newLocation);
	bool intersects();
	void hideAll();
};

#endif // __PLAYER_H__
