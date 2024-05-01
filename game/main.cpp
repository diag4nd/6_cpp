#include <iostream>
#include <fstream>
#include <string>
#include <array>

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
	
	// Create title panel
	int titleHeight(10), titleWidth(59), titleY(yMax/4), titleX(xMax/3);	
	Screen title(titleY, titleX, titleHeight, titleWidth, "title");
	
	// Create menu panel	
	int startHeight(20), startWidth(59), startY(yMax/2), startX(xMax/3 + tuneX);
	Screen menu[8]
	{
		Screen(startY, startX, startHeight, startWidth, "start" + to_string(0)),

		Screen(startY, startX, startHeight, startWidth, "start" + to_string(1)),

		Screen(startY, startX, startHeight, startWidth, "start" + to_string(2)),

		Screen(startY, startX, startHeight, startWidth, "start" + to_string(3)),
	
		Screen(startY, startX, startHeight, startWidth, "game" + to_string(0)),

		Screen(startY, startX, startHeight, startWidth, "game" + to_string(1)),

		Screen(startY, startX, startHeight, startWidth, "game" + to_string(2)),

		Screen(startY, startX, startHeight, startWidth, "game" + to_string(3))
	};
	for (int i = 0; i < 8; i++)
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
			menu[i].~Screen();
		}
		title.~Screen();

		int baloonY(yMax/5), baloonX(xMax/5);

		Player baloon(baloonY, baloonX);
		
		//play(baloon);
	}
	else
	{
		endwin();
	}

	return 0;
}

