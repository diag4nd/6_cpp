#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Monkey.h"
#include "Screen.h"
#include "Banana.h"
#include "Fuel.h"
#include <vector>

using namespace std;

class Player: public Monkey
{
public:
	Player(int _y, int _x, int _h = 6, int _w = 7);
	
	Screen TITLE;
	Screen* MENU;
	Screen HUD;
	Screen* MAPS;
	Screen* END;
	Screen HALL;
	Screen HELP;
	Screen FINISH;
	
	Banana* BANANAS_0;
	Banana* BANANAS_1;
	Banana* BANANAS_2;
	Banana* BANANAS_3;
	Banana* BANANAS_4;
	
	Fuel* FUELS_0;
	Fuel* FUELS_1;
	Fuel* FUELS_2;
	Fuel* FUELS_3;
	Fuel* FUELS_4;

	int choice;
	bool isAlive;
	int location;
	int fuelMax, fuel;
	int menuLen, mapsLen;
	int endLen;
	vector<int> bananaLen;
	vector<int> fuelLen;
	int points, attempts, bananasFound;	

	void move();
	void spendFuel();
	void updateFuel();
	void updatePoints();
	void updateHALL();
	void setHUD(Screen _HUD);
	void setMAPS(Screen* _MAPS);
	void jump(int _newLocation);
	bool intersects();
	void hideAll();
	void reset();
};

#endif // __PLAYER_H__
