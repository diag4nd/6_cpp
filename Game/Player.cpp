#include "functions.h"
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Screen.h"
#include "globals.h"

using namespace std;

Player::Player(int _y, int _x, int _h, int _w): Monkey(_y, _x, _h, _w), points(0), fuelMax(100), fuel(fuelMax), isAlive(true), location(0), choice(0), attempts(0), bananasFound(0)
{
	for (int i = 0; i < 5; i++)
	{
		bananaLen.push_back(0);
	}

	for (int i = 0; i < 5; i++)
	{
		fuelLen.push_back(0);
	}

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
		case 'a':
			if (fuel)
			{
				x-=2;
				y+=1;
				spendFuel();
			}
			break;

		case 'd':
			if (fuel)
			{
				x+=2;
				y+=1;
				spendFuel();
			}
			break;

		case 'w':
			if (fuel)
			{
				y-=2;
				spendFuel();
			}
			break;
		
		case 'q':
			if (fuel)
			{
				y-=2;
				x-=2;
				spendFuel();
			}
			break;

		case 'e':
			if (fuel)
			{
				y-=2;
				x+=2;
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
				jump(3);
			}
			else if (y >= yMax - height + 1 - 5)
			{
				jump(4);
			}
			break;
		case 2:
			if (x < 0)
			{
				jump(1);
			}
			break;
		case 4:
			if (y < 0)
			{
				jump(1);
			}
			break;
		case 3:
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
//	fuel -= 1;
	updateFuel();
}

void Player::updateFuel()
{
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

void Player::updatePoints()
{
	mvwprintw(HUD.win, 2, 133, to_string(points).c_str());

	if (not points)
	{
		for (int i = 134; i < 134 + 5; i++)
		{
			mvwprintw(HUD.win, 2, i, " ");
		}
	}
	
	wrefresh(HUD.win);
}


void Player::jump(int _newLocation)
{
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	
	hide_panel(MAPS[location].pan);
	
	switch(location)
	{
		case 0:
			for (int i = 0; i < bananaLen[0]; i++)
			{
				hide_panel(BANANAS_0[i].pan);
			}
			for (int i = 0; i < fuelLen[0]; i++)
			{
				hide_panel(FUELS_0[i].pan);
			}
			break;
		case 1:
			for (int i = 0; i < bananaLen[1]; i++)
			{
				hide_panel(BANANAS_1[i].pan);
			}
			for (int i = 0; i < fuelLen[1]; i++)
			{
				hide_panel(FUELS_1[i].pan);
			}
			break;
		case 2:
			// TODO
			hide_panel(FINISH.pan);
			for (int i = 0; i < bananaLen[2]; i++)
			{
				hide_panel(BANANAS_2[i].pan);
			}
			for (int i = 0; i < fuelLen[2]; i++)
			{
				hide_panel(FUELS_2[i].pan);
			}
			break;
		case 3:
			for (int i = 0; i < bananaLen[3]; i++)
			{
				hide_panel(BANANAS_3[i].pan);
			}
			for (int i = 0; i < fuelLen[3]; i++)
			{
				hide_panel(FUELS_3[i].pan);
			}
			break;
		case 4:
			for (int i = 0; i < bananaLen[4]; i++)
			{
				hide_panel(BANANAS_4[i].pan);
			}
			for (int i = 0; i < fuelLen[4]; i++)
			{
				hide_panel(FUELS_4[i].pan);
			}
			break;
	}

	show_panel(MAPS[_newLocation].pan);

	switch(_newLocation)
	{
		case 0:
			for (int i = 0; i < bananaLen[0]; i++)
			{
				if (BANANAS_0[i].isActive)
				{
					show_panel(BANANAS_0[i].pan);
				}
			}
			for (int i = 0; i < fuelLen[0]; i++)
			{
				if (FUELS_0[i].isActive)
				{
					show_panel(FUELS_0[i].pan);
				}
			}
			break;
		case 1:
			for (int i = 0; i < bananaLen[1]; i++)
			{
				if (BANANAS_1[i].isActive)
				{
					show_panel(BANANAS_1[i].pan);
				}
			}
			for (int i = 0; i < fuelLen[1]; i++)
			{
				if (FUELS_1[i].isActive)
				{
					show_panel(FUELS_1[i].pan);
				}
			}
			break;
		case 2:
			// TODO
			show_panel(FINISH.pan);
			for (int i = 0; i < bananaLen[2]; i++)
			{
				if (BANANAS_2[i].isActive)
				{
					show_panel(BANANAS_2[i].pan);
				}
			}
			for (int i = 0; i < fuelLen[2]; i++)
			{
				if (FUELS_2[i].isActive)
				{
					show_panel(FUELS_2[i].pan);
				}
			}
			break;
		case 3:
			for (int i = 0; i < bananaLen[3]; i++)
			{
				if (BANANAS_3[i].isActive)
				{
					show_panel(BANANAS_3[i].pan);
				}
			}
			for (int i = 0; i < fuelLen[3]; i++)
			{
				if (FUELS_3[i].isActive)
				{
					show_panel(FUELS_3[i].pan);
				}
			}
			break;
		case 4:
			for (int i = 0; i < bananaLen[4]; i++)
			{
				if (BANANAS_4[i].isActive)
				{
					show_panel(BANANAS_4[i].pan);
				}
			}
			for (int i = 0; i < fuelLen[4]; i++)
			{
				if (FUELS_4[i].isActive)
				{
					show_panel(FUELS_4[i].pan);
				}
			}
			break;
	}

	show_panel(pan);
	
	if (location - _newLocation == -1)
	{
		x = 2;
	}
	else if (location - _newLocation == 1)
	{
		x = xMax - 3 - width;
	}
	else if (location - _newLocation == 2)
	{
		y = 1;
	}
	else if (location - _newLocation == -2)
	{
		y = yMax - 3 - height - 4;
	}
	else if (location - _newLocation == 3)
	{
		y = yMax - 3 - height - 4;
	}
	else if (location - _newLocation == -3)
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

	for (int i = y; i < y + height; i++)
	{
		for (int j = x; j < x + width; j++)
		{
			for (int k = 0; k < bananaLen[location]; k++)
			{
				switch (location)
				{
					case 0:
						if ((j == BANANAS_0[k].x) and (i == BANANAS_0[k].y))
						{
							if (BANANAS_0[k].isActive)
							{
								bananasFound += 1;
								points += BANANAS_0[k].reward;
								BANANAS_0[k].isActive = false;
								updatePoints();
								hide_panel(BANANAS_0[k].pan);
								update_panels();
								doupdate();
							}
						}

						if ((j == FUELS_0[k].x) and (i == FUELS_0[k].y))
						{
							if (FUELS_0[k].isActive)
							{
								fuel = fuelMax;
								updateFuel();
								FUELS_0[k].isActive = false;
								hide_panel(FUELS_0[k].pan);
								update_panels();
								doupdate();
							}
						}
						break;
					case 1:
						if ((j == BANANAS_1[k].x) and (i == BANANAS_1[k].y))
						{
							if (BANANAS_1[k].isActive)
							{
								points += BANANAS_1[k].reward;
								BANANAS_1[k].isActive = false;
								updatePoints();
								hide_panel(BANANAS_1[k].pan);
								update_panels();
								doupdate();
							}
						}

						if ((j == FUELS_1[k].x) and (i == FUELS_1[k].y))
						{
							if (FUELS_1[k].isActive)
							{
								fuel = fuelMax;
								updateFuel();
								FUELS_1[k].isActive = false;
								hide_panel(FUELS_1[k].pan);
								update_panels();
								doupdate();
							}
						}
						break;
					case 2:
						if ((j == BANANAS_2[k].x) and (i == BANANAS_2[k].y))
						{
							if (BANANAS_2[k].isActive)
							{
								points += BANANAS_2[k].reward;
								BANANAS_2[k].isActive = false;
								updatePoints();
								hide_panel(BANANAS_2[k].pan);
								update_panels();
								doupdate();
							}
						}

						if ((j == FUELS_2[k].x) and (i == FUELS_2[k].y))
						{
							if (FUELS_2[k].isActive)
							{
								fuel = fuelMax;
								updateFuel();
								FUELS_2[k].isActive = false;
								hide_panel(FUELS_2[k].pan);
								update_panels();
								doupdate();
							}
						}
						if ((i == FINISH.y) and (j == FINISH.x))
						{
							//TODO
							choice = 0;
							show_panel(END[2 + choice].pan);
							update_panels();
							doupdate();
							finish(*this);
						}

						break;
					case 3:
						if ((j == BANANAS_3[k].x) and (i == BANANAS_3[k].y))
						{
							if (BANANAS_3[k].isActive)
							{
								points += BANANAS_3[k].reward;
								BANANAS_3[k].isActive = false;
								updatePoints();
								hide_panel(BANANAS_3[k].pan);
								update_panels();
								doupdate();
							}
						}

						if ((j == FUELS_3[k].x) and (i == FUELS_3[k].y))
						{
							if (FUELS_3[k].isActive)
							{
								fuel = fuelMax;
								updateFuel();
								FUELS_3[k].isActive = false;
								hide_panel(FUELS_3[k].pan);
								update_panels();
								doupdate();
							}
						}
						break;
					case 4:
						if ((j == BANANAS_4[k].x) and (i == BANANAS_4[k].y))
						{
							if (BANANAS_4[k].isActive)
							{
								points += BANANAS_4[k].reward;
								BANANAS_4[k].isActive = false;
								updatePoints();
								hide_panel(BANANAS_4[k].pan);
								update_panels();
								doupdate();
							}
						}

						if ((j == FUELS_4[k].x) and (i == FUELS_4[k].y))
						{
							if (FUELS_4[k].isActive)
							{
								fuel = fuelMax;
								updateFuel();
								FUELS_4[k].isActive = false;
								hide_panel(FUELS_4[k].pan);
								update_panels();
								doupdate();
							}
						}
						break;
				}
			}			
		}
	}
	
	return false;
}

void Player::hideAll()
{
	hide_panel(TITLE.pan);

	for (int i = 0; i < menuLen; i++)
	{
		hide_panel(MENU[i].pan);
	}
	
	for (int i = 0; i < mapsLen; i++)
	{
		hide_panel(MAPS[i].pan);
	}
	
	for (int i = 0; i < endLen; i++)
	{
		hide_panel(END[i].pan);
	}

	hide_panel(HUD.pan);
	hide_panel(pan);	
}

void Player::reset()
{
	// Get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	int baloonY(yMax/5), baloonX(xMax/5);
	
	y = baloonY; 
	x = baloonX;
	location = 0;
	
	fuel = 100;
	updateFuel();
	
	points = 0;
	updatePoints();

	isAlive = true;
	
	for (int i = 0; i < bananaLen[0]; i++)
	{
		BANANAS_0[i].isActive = true;
	}
	for (int i = 0; i < fuelLen[0]; i++)
	{
		FUELS_0[i].isActive = true;
	}

	for (int i = 0; i < bananaLen[1]; i++)
	{
		BANANAS_1[i].isActive = true;
	}
	for (int i = 0; i < fuelLen[1]; i++)
	{
		FUELS_1[i].isActive = true;
	}

	for (int i = 0; i < bananaLen[2]; i++)
	{
		BANANAS_2[i].isActive = true;
	}
	for (int i = 0; i < fuelLen[2]; i++)
	{
		FUELS_2[i].isActive = true;
	}

	for (int i = 0; i < bananaLen[3]; i++)
	{
		BANANAS_3[i].isActive = true;
	}
	for (int i = 0; i < fuelLen[3]; i++)
	{
		FUELS_3[i].isActive = true;
	}

	for (int i = 0; i < bananaLen[4]; i++)
	{
		BANANAS_4[i].isActive = true;
	}
	for (int i = 0; i < fuelLen[4]; i++)
	{
		FUELS_4[i].isActive = true;
	}

}
