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
#include "Enemy.cpp"

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
	int mapHeight(yMax - 5), mapWidth(xMax - 1), mapY(0), mapX(0), mapLen = 5;
	Screen MAPS[mapLen]
	{
		Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(0)),

		Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(1)),

		Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(2)),
			
		Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(3)),
			
		Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(4))
	};	
	for (int i = 0; i < mapLen; i++)
	{
		hide_panel(MAPS[i].pan);
	}
		
	// Create HUD
	int hudY(yMax - 5), hudX(0), hudHeight(5), hudWidth(xMax);
	Screen HUD(hudY, hudX, hudHeight, hudWidth, "hud");
	hide_panel(HUD.pan);
	
	// Create END menu
	int endHeight(10), endWidth(29), endY(yMax/3 + tuneY), endX(xMax/3 + tuneX + 3), endLen = 2;
	Screen END[endLen]
	{
		Screen(endY, endX, endHeight, endWidth, "gameover/end" + to_string(0)),

		Screen(endY, endX, endHeight, endWidth, "gameover/end" + to_string(1))
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
	baloon.TITLE = TITLE;
	baloon.MENU = MENU;
	baloon.END = END;
	baloon.HALL = HALL;
	baloon.HELP = HELP;

	// Setting what user observes
	show_panel(baloon.TITLE.pan);
	show_panel(baloon.MENU[0].pan);
	update_panels();
	doupdate();
	
	navigate(baloon);
	endwin();
	return 0;
}

