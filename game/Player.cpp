#include "functions.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Screen.h"

using namespace std;

Player::Player(int _y, int _x, int _h, int _w): Monkey(_y, _x, _h, _w), points(0), fuel(100), isAlive(true), location(0)

{
	ifstream fRead;
	string line;
	int idx = 0;
	fRead.open(".game/sprites/player");
	while (getline(fRead, line))
	{
		mvwprintw(win, idx, 0, line.c_str());
		idx += 1;
	}
	fRead.close();
	wrefresh(win);	
}

void Player::move()
{
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	switch (getch())
	{
		case KEY_LEFT:
		case 'a':
			if (fuel)
			{
				x-=2;
				y+=1;
				spendFuel();
			}
			break;

		case KEY_RIGHT:
		case 'd':
			if (fuel)
			{
				x+=2;
				y+=1;
				spendFuel();
			}
			break;

		case KEY_UP:
		case 'w':
			if (fuel)
			{
				y-=2;
				spendFuel();
			}
			break;
			
		case ERR:
			y+=1;
			break;
	}
	switch (location)
	{
		case 0:
			if ((x <= 1) or (y <= 1) or (y >= yMax - height - 6 + 1))
			{	
				isAlive = false;
			}
			else if (x >= xMax - width + 2)
			{
				jump(1);
			}
			else
			{
				move_panel(pan, y, x);
				update_panels();
				doupdate();
			}
			
			break;
	}
}

void Player::spendFuel()
{
	//fuel--;
	/*
	for (int i = 0; i < 100; i++)
	{
		if (i < fuel)
		{
			mvwprintw(HUD.win, 2, 8 + i, "X");
		}
		else
		{

			mvwprintw(HUD.win, 2, 8 + i, " ");
		}
	}
	wrefresh(HUD.win);
	*/
}

void Player::jump(int _newLocation)
{
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	hide_panel(MAPS[location].pan);
	show_panel(MAPS[_newLocation].pan);
	show_panel(pan);
	
	if (location < _newLocation)
	{
		move_panel(pan, y, 2);
	}
	else
	{
		move_panel(pan, y, xMax - 2 - width);
	}
	
	location = _newLocation;

	update_panels();
	doupdate();
}

