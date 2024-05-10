#include "panel.h"
#include "functions.h"
#include "globals.h"
#include "Screen.h"
#include "Player.h"


int navigate(int _idx, Screen* _menu)
{	
	switch (getch())
	{
		case KEY_DOWN:
		case 's':
			choice = (1 + choice)%4 + choice/4 * 4;
			hide_panel(_menu[_idx].pan);
			show_panel(_menu[choice].pan);
			update_panels();
			doupdate();
			navigate(choice, _menu);
			break;

		case KEY_UP:	
		case 'w':
			choice = (3 + choice)%4 + choice/4 * 4;
			hide_panel(_menu[_idx].pan);
			show_panel(_menu[choice].pan);
			update_panels();
			doupdate();
			navigate(choice, _menu);
			break;

		case KEY_BACKSPACE:
			choice = 3 + choice/4 * 4;
			hide_panel(_menu[_idx].pan);
			show_panel(_menu[choice].pan);
			update_panels();
			doupdate();
			navigate(choice, _menu);
			break;

		case 10:
		case ' ':
			switch (choice)
			{
				case 0:
					choice = 4;
					hide_panel(_menu[_idx].pan);
					show_panel(_menu[choice].pan);
					update_panels();
					doupdate();
					navigate(choice, _menu);
					break;
				case 1:
					navigate(choice, _menu);
					break;
				case 2:
					navigate(choice, _menu);
					break;
				case 3:
					return 0;
				case 4:
					choice = 0;
					return 1;
				case 5:
					navigate(choice, _menu);
					break;
				case 6:
					navigate(choice, _menu);
					break;
				case 7:
					choice = 0;
					hide_panel(_menu[_idx].pan);
					show_panel(_menu[choice].pan);
					update_panels();
					doupdate();
					navigate(choice, _menu);
					break;
			}
	}
}

void play(Player _baloon)
{
	for (int i = 0; i < _baloon.mapLen; i++)
	{
		hide_panel(_baloon.MAPS[i].pan);
	}
		
	hide_panel(_baloon.HUD.pan);

	// Get screen size
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	int baloonY(yMax/5), baloonX(xMax/5);
	
	_baloon.y = baloonY; 
	_baloon.x = baloonX;
	_baloon.location = 0;
	_baloon.fuel = 100;
	_baloon.isAlive = true;
	
	show_panel(_baloon.MAPS[_baloon.location].pan);
	show_panel(_baloon.HUD.pan);
	show_panel(_baloon.pan);

	move_panel(_baloon.pan, _baloon.y, _baloon.x);
	update_panels();
	doupdate();

	halfdelay(ovrlDel);

	while (_baloon.isAlive)
	{
		_baloon.move();
	}
	
	play(_baloon);	
}
