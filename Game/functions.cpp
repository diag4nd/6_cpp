#include "panel.h"
#include "functions.h"
#include "globals.h"
#include "Screen.h"
#include "Player.h"

void navigate(Player _baloon)
{	
	raw();
	switch (getch())
	{
		case KEY_DOWN:
		case 's':
			hide_panel(_baloon.MENU[_baloon.choice].pan);
			_baloon.choice = (1 + _baloon.choice)%4 + _baloon.choice/4 * 4;
			show_panel(_baloon.MENU[_baloon.choice].pan);
			update_panels();
			doupdate();
			navigate(_baloon);
			break;

		case KEY_UP:	
		case 'w':	
			hide_panel(_baloon.MENU[_baloon.choice].pan);
			_baloon.choice = (3 + _baloon.choice)%4 + _baloon.choice/4 * 4;
			show_panel(_baloon.MENU[_baloon.choice].pan);
			update_panels();
			doupdate();
			navigate(_baloon);
			break;

		case KEY_BACKSPACE:
			hide_panel(_baloon.MENU[_baloon.choice].pan);
			_baloon.choice = 3 + _baloon.choice/4 * 4;
			show_panel(_baloon.MENU[_baloon.choice].pan);
			update_panels();
			doupdate();
			navigate(_baloon);
			break;

		case 10:
		case ' ':
			switch (_baloon.choice)
			{
				case 0:
					hide_panel(_baloon.MENU[_baloon.choice].pan);
					_baloon.choice = 4;
					show_panel(_baloon.MENU[_baloon.choice].pan);
					update_panels();
					doupdate();
					
					navigate(_baloon);
					break;
				case 1:
					hide_panel(_baloon.MENU[_baloon.choice].pan);
					show_panel(_baloon.HELP.pan);
					update_panels();
					doupdate();

					help(_baloon);
					break;
				case 2:
					hide_panel(_baloon.MENU[_baloon.choice].pan);
					show_panel(_baloon.HALL.pan);
					update_panels();
					doupdate();

					hallOfFame(_baloon);
					break;
				case 3:
					endwin();
					return;
				case 4:
					play(_baloon);
					break;
				case 5:
					navigate(_baloon);
					break;
				case 6:
					navigate(_baloon);
					break;
				case 7:
					hide_panel(_baloon.MENU[_baloon.choice].pan);
					_baloon.choice = 0;
					show_panel(_baloon.MENU[_baloon.choice].pan);
					update_panels();
					doupdate();
					
					navigate(_baloon);
					break;
			}
			break;
		default:
			navigate(_baloon);
			break;
	}

}

void play(Player _baloon)
{
	hide_panel(_baloon.MENU[_baloon.choice].pan);
	
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

	nocbreak();
	_baloon.choice  = 0;
	show_panel(_baloon.END[_baloon.choice].pan);
	update_panels();
	doupdate();

	gameOver(_baloon);
}

void gameOver(Player _baloon)
{	
	raw();
	switch (getch())
	{
		case KEY_DOWN:
		case 's':
			hide_panel(_baloon.END[_baloon.choice].pan);
			_baloon.choice = not _baloon.choice;
			show_panel(_baloon.END[_baloon.choice].pan);
			update_panels();
			doupdate();
			gameOver(_baloon);
			break;

		case KEY_UP:
		case 'w':	
			hide_panel(_baloon.END[_baloon.choice].pan);
			_baloon.choice = not _baloon.choice;
			show_panel(_baloon.END[_baloon.choice].pan);
			update_panels();
			doupdate();
			gameOver(_baloon);
			break;

		case 10:
		case ' ':
			switch (_baloon.choice)
			{
				case 0:
					hide_panel(_baloon.END[_baloon.choice].pan);
					play(_baloon);
					break;
				case 1:
					hide_panel(_baloon.END[_baloon.choice].pan);
					hide_panel(_baloon.MAPS[_baloon.location].pan);
					hide_panel(_baloon.HUD.pan);
					hide_panel(_baloon.pan);
					
					_baloon.choice = 0;
					show_panel(_baloon.MENU[_baloon.choice].pan);
					update_panels();
					doupdate();

					navigate(_baloon);
					break;
			}
			break;
		default:
			gameOver(_baloon);
			break;
	}

}

void hallOfFame(Player _baloon)
{	
	raw();
	switch (getch())
	{
		case KEY_BACKSPACE:
			hide_panel(_baloon.HALL.pan);
			_baloon.choice = 0;
			show_panel(_baloon.MENU[_baloon.choice].pan);
			update_panels();
			doupdate();
			
			navigate(_baloon);
			break;

		default:
			hallOfFame(_baloon);
			break;
	}
}

void help(Player _baloon)
{	
	raw();
	switch (getch())
	{
		case KEY_BACKSPACE:
			hide_panel(_baloon.HELP.pan);
			_baloon.choice = 0;
			show_panel(_baloon.MENU[_baloon.choice].pan);
			update_panels();
			doupdate();
			
			navigate(_baloon);
			break;

		default:
			help(_baloon);
			break;
	}
}
