#include "functions.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Screen.h"
#include "globals.h"

using namespace std;

Player::Player(int _y, int _x, int _h, int _w): Monkey(_y, _x, _h, _w), points(0), fuelMax(100), fuel(fuelMax), isAlive(true), location(0)

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
				x-=3;
				y+=1;
				spendFuel();
			}
			break;

		case KEY_RIGHT:
		case 'd':
			if (fuel)
			{
				x+=3;
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
			if (x > xMax - width - 1)
			{
				jump(1);
			}			
			break;
		case 1:
			if (x < 0)
			{
				jump(0);
			}
			else if (x > xMax - width - 1)
			{
				jump(2);
			}
			else if (y < 0)
			{
				jump(4);
			}
			else if (y >= yMax - height + 1 - 5)
			{
				jump(3);
			}
			break;
		case 2:
			if (x < 0)
			{
				jump(1);
			}
			break;
		case 3:
			if (y < 0)
			{
				jump(1);
			}
			break;
		case 4:
			if (y >= yMax - height + 1 - 5)
			{
				jump(1);
			}
			break;

	}
	if (intersects())
	{
		isAlive = false;
	}
	else
	{
		move_panel(pan, y, x);
		update_panels();
		doupdate();
	}		
}

void Player::spendFuel()
{
	//fuel--;
	for (int i = 0; i < fuelMax; i++)
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
}

void Player::jump(int _newLocation)
{
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	hide_panel(MAPS[location].pan);
	show_panel(MAPS[_newLocation].pan);
	show_panel(pan);
	
	if (location - _newLocation == -1)
	{
		x = 2;
	}
	else if (location - _newLocation == 1)
	{
		x = xMax - 3 - width;
	}
	else if (location - _newLocation == -2)
	{
		y = 1;
	}
	else if (location - _newLocation == 2)
	{
		y = yMax - 3 - height - 5;
	}
	else if (location - _newLocation == -3)
	{
		y = yMax - 3 - height - 5;
	}
	else if (location - _newLocation == 3)
	{
		y = 1;
	}

	
	move_panel(pan, y, x);
	
	location = _newLocation;
	update_panels();
	doupdate();
}

bool Player::intersects()
{
	ifstream fRead;
	
	fRead.open((".game/sprites/maps/map" + to_string(location)).c_str());
	
	int i = 0;

	std::string line;
	while (std::getline(fRead, line))
	{		
		i++;

		if (i >= y + 1 and i < y + height + 1)
		{
			for (int j = x - 1; j < x + width; j++)
			{
				if (line[j] == '#')
				{
					return true;
				}
			}
		}
	}	

	fRead.close();
	
	return false;
}

