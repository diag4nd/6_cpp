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
	choice = 0;
	initscr();
	noecho();			// To not see what user types
	curs_set(0);			// To make cursor invincible
	keypad(stdscr, true);		// To work with arrows
	raw();

	// Get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	// Create title panel
	int titleHeight(10), titleWidth(59), titleY(yMax/4), titleX(xMax/3);	
	Screen title(titleY, titleX, titleHeight, titleWidth, "title");
	
	// Create menu panel	
	int startHeight(20), startWidth(59), startY(yMax/2), startX(xMax/3 + tuneX), menuLen(8);
	Screen menu[menuLen]
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
		hide_panel(menu[i].pan);
	}


	// Setting what user observes
	show_panel(menu[0].pan);
	update_panels();
	doupdate();
	
	if (navigate(choice, menu))
	{
		for (int i = 0; i < 8; i++)
		{
			hide_panel(menu[i].pan);
		}
		hide_panel(title.pan);	
		
		// Create maps
		int mapHeight(yMax - 5), mapWidth(xMax), mapY(0), mapX(0);
		Screen MAPS[3]
		{
			Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(0)),

			Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(1)),

			Screen(mapY, mapX, mapHeight, mapWidth, "maps/map" + to_string(2)),
		};
		for (int i = 0; i < 3; i++)
		{
			hide_panel(MAPS[i].pan);
		}
		hide_panel(MAPS[0].pan);
		
		// Create HUD
		int hudY(yMax - 5), hudX(0), hudHeight(5), hudWidth(xMax);
		Screen HUD(hudY, hudX, hudHeight, hudWidth, "hud");
		hide_panel(HUD.pan);
		
		// Create player
		int baloonY(yMax/5), baloonX(xMax/5);
		Player baloon(baloonY, baloonX);
		baloon.HUD = HUD;
		baloon.MAPS = MAPS;
		
		show_panel(baloon.HUD.pan);
		show_panel(baloon.MAPS[0].pan);
		show_panel(baloon.pan);

		update_panels();
		doupdate();

		if (play(baloon))
		{
			clear();
			refresh();
			endwin();
		}
	}
	else
	{
		endwin();
	}
	getch();
	endwin();
	return 0;
}

