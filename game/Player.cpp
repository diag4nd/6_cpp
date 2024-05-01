#include "functions.h"
#include "Player.h"
#include <fstream>
#include <string>

using namespace std;

Player::Player(int _y, int _x, int _h, int _w): Monkey(_y, _x, _h, _w), points{0}, fuel{500}
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
			x-=2;
			y+=1;
			break;
		case KEY_RIGHT:
		case 'd':
			x+=2;
			y+=1;
			break;
		case KEY_UP:
		case 'w':
			if (fuel)
			{
				y-=2;
				fuel--;
			}
			break;
		case ERR:
			y+=1;
			break;
	}
	if ((x <= 0) or (x >= xMax - width + 1) or (y <= 0) or (y >= yMax - height + 1))
	{
		this->~Monkey();
		endwin();
		main();
	}
	else
	{
		move_panel(pan, y, x);
		update_panels();
		doupdate();
	}
}
