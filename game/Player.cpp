#include "functions.h"
#include "Player.h"
#include <fstream>
#include <string>
#include "Screen.h"

using namespace std;

Player::Player(int _y, int _x, int _h, int _w): Monkey(_y, _x, _h, _w), points(0), fuel(100), isAlive(true)

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
	
	if ((x <= 0) or (x >= xMax - width + 1) or (y <= 0) or (y >= yMax - height - 5 + 1))
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
	fuel--;
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
}
