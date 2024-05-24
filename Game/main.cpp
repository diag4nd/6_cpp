#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdio.h>

#include "globals.cpp"
#include "functions.cpp"
#include "Monkey.cpp"
#include "Screen.cpp"
#include "Player.cpp"
#include "Banana.cpp"
#include "Fuel.cpp"

using namespace std;

int main()
{		
	// Setting initial parameters
	initscr();
	noecho();			// To not see what user types
	curs_set(0);			// To make cursor invincible
	keypad(stdscr, true);		// To work with arrows

	// Get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	// Create TITLE panel
	int titleHeight(10), titleWidth(59), titleY(yMax/4), titleX(xMax/3);	
	Screen TITLE(titleY, titleX, titleHeight, titleWidth, "title");
	hide_panel(TITLE.pan);
	
	// Create MENU panel	
	int startHeight(20), startWidth(59), startY(yMax/2), startX(xMax/3 + tuneX + 5), menuLen(8);
	Screen MENU[menuLen]
	{
		Screen(startY, startX, startHeight, startWidth, "menu/start" + to_string(0)),

		Screen(startY, startX, startHeight, startWidth, "menu/start" + to_string(1)),

		Screen(startY, startX, startHeight, startWidth, "menu/start" + to_string(2)),

		Screen(startY, startX, startHeight, startWidth, "menu/start" + to_string(3)),
	
		Screen(startY, startX, startHeight, startWidth, "menu/game" + to_string(0)),

		Screen(startY, startX, startHeight, startWidth, "menu/game" + to_string(1)),

		Screen(startY, startX, startHeight, startWidth, "menu/game" + to_string(2)),

		Screen(startY, startX, startHeight, startWidth, "menu/game" + to_string(3))
	};
	for (int i = 0; i < menuLen; i++)
	{
		hide_panel(MENU[i].pan);
	}

	// Create MAPS
	int mapHeight(yMax - 5), mapWidth(xMax - 1), mapY(0), mapX(0), mapsLen(5);
	Screen MAPS[mapsLen]
	{
		Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(0)),

		Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(1)),

		Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(2)),
			
		Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(3)),
			
		Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(4))
	};	
	for (int i = 0; i < mapsLen; i++)
	{
		hide_panel(MAPS[i].pan);
	}	

	// Create BANANAS
	int bananaHeight(1), bananaWidth(1);
	
	int bananaLen_0(3);
	Banana BANANAS_0[bananaLen_0]
	{
		Banana(8, 54, bananaHeight, bananaWidth, "banana"),
		
		Banana(31, 169, bananaHeight, bananaWidth, "banana"),

		Banana(44, 7, bananaHeight, bananaWidth, "banana")
	};
	for (int i = 0; i < bananaLen_0; i++)
	{
		hide_panel(BANANAS_0[i].pan);
	}
	
	int bananaLen_1(2);
	Banana BANANAS_1[bananaLen_1]
	{
		Banana(28, 152, bananaHeight, bananaWidth, "banana"),

		Banana(11, 48, bananaHeight, bananaWidth, "banana")
	};
	
	for (int i = 0; i < bananaLen_1; i++)
	{
		hide_panel(BANANAS_1[i].pan);
	}
	
	int bananaLen_2(2);
	Banana BANANAS_2[bananaLen_2]
	{
		Banana(7, 134, bananaHeight, bananaWidth, "banana"),

		Banana(46, 18, bananaHeight, bananaWidth, "banana")
	};
	
	for (int i = 0; i < bananaLen_2; i++)
	{
		hide_panel(BANANAS_2[i].pan);
	}
	
	int bananaLen_3(7);
	Banana BANANAS_3[bananaLen_3]
	{
		Banana(16, 150, bananaHeight, bananaWidth, "banana"),
		
		Banana(14, 157, bananaHeight, bananaWidth, "banana"),
		
		Banana(17, 165, bananaHeight, bananaWidth, "banana"),
		
		Banana(20, 157, bananaHeight, bananaWidth, "banana"),
		
		Banana(24, 160, bananaHeight, bananaWidth, "banana"),
		
		Banana(27, 150, bananaHeight, bananaWidth, "banana"),
		
		Banana(24, 145, bananaHeight, bananaWidth, "banana")
	};
	
	for (int i = 0; i < bananaLen_3; i++)
	{
		hide_panel(BANANAS_3[i].pan);
	}

	int bananaLen_4(4);
	Banana BANANAS_4[bananaLen_4]
	{
		Banana(7, 13, bananaHeight, bananaWidth, "banana"),
		
		Banana(41, 75, bananaHeight, bananaWidth, "banana"),
		
		Banana(7, 163, bananaHeight, bananaWidth, "banana"),

		Banana(18, 117, bananaHeight, bananaWidth, "banana")
	};
	
	for (int i = 0; i < bananaLen_4; i++)
	{
		hide_panel(BANANAS_4[i].pan);
	}

	// Create FUELS
	int fuelHeight(1), fuelWidth(1);
	int fuelLen_0(2);
	Fuel FUELS_0[fuelLen_0]
	{
		Fuel(45, 89, fuelHeight, fuelWidth, "fuel"),

		Fuel(22, 125, fuelHeight, fuelWidth, "fuel")
	};
	for (int i = 0; i < fuelLen_0; i++)
	{
		hide_panel(FUELS_0[i].pan);
	}

	int fuelLen_1(2);
	Fuel FUELS_1[fuelLen_1]
	{
		Fuel(6, 163, fuelHeight, fuelWidth, "fuel"),

		Fuel(44, 60, fuelHeight, fuelWidth, "fuel")
	};
	for (int i = 0; i < fuelLen_1; i++)
	{
		hide_panel(FUELS_1[i].pan);
	}

	int fuelLen_2(1);
	Fuel FUELS_2[fuelLen_2]
	{
		//Fuel(0, 0, fuelHeight, fuelWidth, "fuel"),

		Fuel(46, 72, fuelHeight, fuelWidth, "fuel")
	};
	for (int i = 0; i < fuelLen_2; i++)
	{
		hide_panel(FUELS_2[i].pan);
	}

	int fuelLen_3(2);
	Fuel FUELS_3[fuelLen_3]
	{
		Fuel(16, 128, fuelHeight, fuelWidth, "fuel"),

		Fuel(32, 127, fuelHeight, fuelWidth, "fuel")
	};
	for (int i = 0; i < fuelLen_3; i++)
	{
		hide_panel(FUELS_3[i].pan);
	}

	int fuelLen_4(2);
	Fuel FUELS_4[fuelLen_4]
	{
		Fuel(10, 118, fuelHeight, fuelWidth, "fuel"),

		Fuel(42, 11, fuelHeight, fuelWidth, "fuel")
	};
	for (int i = 0; i < fuelLen_4; i++)
	{
		hide_panel(FUELS_4[i].pan);
	}
	
	// Create FINISH FLAG
	int finishHeight(7), finishWidth(10), finishY(26), finishX(155);	
	Screen FINISH(finishY, finishX, finishHeight, finishWidth, "finish");
	hide_panel(FINISH.pan);

	// Create HUD
	int hudY(yMax - 5), hudX(0), hudHeight(5), hudWidth(xMax);
	Screen HUD(hudY, hudX, hudHeight, hudWidth, "hud");
	hide_panel(HUD.pan);
	
	// Create END menu
	int endHeight(10), endWidth(29), endY(yMax/3 + tuneY), endX(xMax/3 + tuneX + 3), endLen = 5;
	Screen END[endLen]
	{
		Screen(endY, endX, endHeight, endWidth, "gameover/end" + to_string(0)),
		
		Screen(endY, endX, endHeight, endWidth, "gameover/end" + to_string(1)),
		
		Screen(endY, endX, endHeight, endWidth, "gameover/end" + to_string(2)),
		
		Screen(endY, endX, endHeight, endWidth, "gameover/end" + to_string(3)),

		Screen(endY, endX, endHeight, endWidth, "gameover/end" + to_string(4))
	};	
	for (int i = 0; i < endLen; i++)
	{
		hide_panel(END[i].pan);
	}
	
	// Create HALL
	int hallY(yMax/4), hallX(xMax/5 + 6), hallHeight(23), hallWidth(93);
	Screen HALL(hallY, hallX, hallHeight, hallWidth, "top10");
	hide_panel(HALL.pan);
	
	// Create HELP
	int helpY(yMax/4 - 5), helpX(xMax/5 + 4), helpHeight(35), helpWidth(100);
	Screen HELP(helpY, helpX, helpHeight, helpWidth, "help");
	hide_panel(HELP.pan);

	// Create PLAYER
	int baloonY(yMax/5), baloonX(xMax/5);
	Player baloon(baloonY, baloonX);
	hide_panel(baloon.pan);
	
	baloon.HUD = HUD;

	baloon.MAPS = MAPS;
	baloon.mapsLen - mapsLen;
	
	baloon.TITLE = TITLE;
	
	baloon.MENU = MENU;
	baloon.menuLen = menuLen;

	baloon.END = END;
	baloon.endLen = endLen;
	
	baloon.HALL = HALL;
	
	baloon.HELP = HELP;
	
	//
	baloon.BANANAS_0 = BANANAS_0;
	baloon.bananaLen[0] = bananaLen_0;
	
	baloon.BANANAS_1 = BANANAS_1;
	baloon.bananaLen[1] = bananaLen_1;

	baloon.BANANAS_2 = BANANAS_2;
	baloon.bananaLen[2] = bananaLen_2;

	baloon.BANANAS_3 = BANANAS_3;
	baloon.bananaLen[3] = bananaLen_3;

	baloon.BANANAS_4 = BANANAS_4;
	baloon.bananaLen[4] = bananaLen_4;
	
	//
	baloon.FUELS_0 = FUELS_0;
	baloon.fuelLen[0] = fuelLen_0;

	baloon.FUELS_1 = FUELS_1;
	baloon.fuelLen[1] = fuelLen_1;

	baloon.FUELS_2 = FUELS_2;
	baloon.fuelLen[2] = fuelLen_2;

	baloon.FUELS_3 = FUELS_3;
	baloon.fuelLen[3] = fuelLen_3;

	baloon.FUELS_4 = FUELS_4;
	baloon.fuelLen[4] = fuelLen_4;
	
	//
	baloon.FINISH = FINISH;
	
	// Setting what user observes
	show_panel(baloon.TITLE.pan);
	show_panel(baloon.MENU[0].pan);
	update_panels();
	doupdate();
	
	navigate(baloon);
	endwin();
	return 0;
}

