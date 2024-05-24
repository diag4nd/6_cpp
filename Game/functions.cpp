#include "panel.h"
#include "functions.h"
#include "globals.h"
#include "Screen.h"
#include "Player.h"

void navigate(Player _baloon)
{	
	curs_set(0);
	noecho();
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
					exit(0);
				case 4:
					_baloon.attempts = 0;
					_baloon.bananasFound = 0;
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
	_baloon.attempts += 1;

	hide_panel(_baloon.MENU[_baloon.choice].pan);
	
	_baloon.reset();
	
	show_panel(_baloon.MAPS[_baloon.location].pan);
	for (int i = 0; i < _baloon.bananaLen[0]; i++)
	{	
		show_panel(_baloon.BANANAS_0[i].pan);
	}
	for (int i = 0; i < _baloon.fuelLen[0]; i++)
	{	
		show_panel(_baloon.FUELS_0[i].pan);
	}
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
					hide_panel(_baloon.FINISH.pan);
					play(_baloon);
					break;
				case 1:
					hide_panel(_baloon.END[_baloon.choice].pan);	
					hide_panel(_baloon.MAPS[_baloon.location].pan);
					hide_panel(_baloon.HUD.pan);
					hide_panel(_baloon.pan);
					hide_panel(_baloon.FINISH.pan);
					
					for (int i = 0; i < _baloon.bananaLen[_baloon.location]; i++)
					{
						switch (_baloon.location)
						{
							case 0:
								hide_panel(_baloon.BANANAS_0[i].pan);
								break;
							case 1:
								hide_panel(_baloon.BANANAS_1[i].pan);
								break;
							case 2:
								hide_panel(_baloon.BANANAS_2[i].pan);
								break;
							case 3:
								hide_panel(_baloon.BANANAS_3[i].pan);
								break;
							case 4:
								hide_panel(_baloon.BANANAS_4[i].pan);
								break;
						}
					}

					for (int i = 0; i < _baloon.fuelLen[_baloon.location]; i++)
					{
						switch (_baloon.location)
						{
							case 0:
								hide_panel(_baloon.FUELS_0[i].pan);
								break;
							case 1:
								hide_panel(_baloon.FUELS_1[i].pan);
								break;
							case 2:
								hide_panel(_baloon.FUELS_2[i].pan);
								break;
							case 3:
								hide_panel(_baloon.FUELS_3[i].pan);
								break;
							case 4:
								hide_panel(_baloon.FUELS_4[i].pan);
								break;
						}
					}

					_baloon.choice = 0;
					show_panel(_baloon.MENU[_baloon.choice].pan);
					update_panels();
					doupdate();

					navigate(_baloon);
					break;
			}
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

void finish(Player _baloon)
{
	raw();
	switch (getch())
	{
		case KEY_DOWN:
		case 's':
			hide_panel(_baloon.END[2 + _baloon.choice].pan);
			_baloon.choice = not _baloon.choice;
			show_panel(_baloon.END[2 + _baloon.choice].pan);
			update_panels();
			doupdate();
			finish(_baloon);
			break;

		case KEY_UP:
		case 'w':	
			hide_panel(_baloon.END[2 + _baloon.choice].pan);
			_baloon.choice = not _baloon.choice;
			show_panel(_baloon.END[2 + _baloon.choice].pan);
			update_panels();
			doupdate();
			finish(_baloon);
			break;

		case 10:
		case ' ':
			switch (_baloon.choice)
			{
				case 0:
					hide_panel(_baloon.END[2 + _baloon.choice].pan);
					_baloon.choice = 4;
					show_panel(_baloon.END[_baloon.choice].pan);
					update_panels();
					doupdate();
					save(_baloon);
					//endwin();
					//exit(0);
					break;
				case 1:
					
					hide_panel(_baloon.END[2 + _baloon.choice].pan);
					hide_panel(_baloon.FINISH.pan);
					hide_panel(_baloon.MAPS[_baloon.location].pan);
					hide_panel(_baloon.HUD.pan);
					hide_panel(_baloon.pan);
					
					for (int i = 0; i < _baloon.bananaLen[_baloon.location]; i++)
					{
						switch (_baloon.location)
						{
							case 0:
								hide_panel(_baloon.BANANAS_0[i].pan);
								break;
							case 1:
								hide_panel(_baloon.BANANAS_1[i].pan);
								break;
							case 2:
								hide_panel(_baloon.BANANAS_2[i].pan);
								break;
							case 3:
								hide_panel(_baloon.BANANAS_3[i].pan);
								break;
							case 4:
								hide_panel(_baloon.BANANAS_4[i].pan);
								break;
						}
					}

					for (int i = 0; i < _baloon.fuelLen[_baloon.location]; i++)
					{
						switch (_baloon.location)
						{
							case 0:
								hide_panel(_baloon.FUELS_0[i].pan);
								break;
							case 1:
								hide_panel(_baloon.FUELS_1[i].pan);
								break;
							case 2:
								hide_panel(_baloon.FUELS_2[i].pan);
								break;
							case 3:
								hide_panel(_baloon.FUELS_3[i].pan);
								break;
							case 4:
								hide_panel(_baloon.FUELS_4[i].pan);
								break;
						}
					}

					_baloon.choice = 0;
					show_panel(_baloon.MENU[_baloon.choice].pan);
					update_panels();
					doupdate();

					navigate(_baloon);
					
					break;
			}	
		default:
			finish(_baloon);
			break;

	}
}

void save(Player _baloon)
{
	
	curs_set(1);
	echo();
	char str[23];
	mvwgetstr(_baloon.END[4].win, 5, 3, str);
	//clear();
	//printw(str);
	//refresh();
	getch();
	
	hide_panel(_baloon.END[_baloon.choice].pan);
	
	//hide_panel(_baloon.END[2 + _baloon.choice].pan);
	hide_panel(_baloon.FINISH.pan);
	hide_panel(_baloon.MAPS[_baloon.location].pan);
	hide_panel(_baloon.HUD.pan);
	hide_panel(_baloon.pan);
					
	for (int i = 0; i < _baloon.bananaLen[_baloon.location]; i++)
	{
		switch (_baloon.location)
		{
			case 0:
				hide_panel(_baloon.BANANAS_0[i].pan);
				break;
			case 1:
				hide_panel(_baloon.BANANAS_1[i].pan);
				break;
			case 2:
				hide_panel(_baloon.BANANAS_2[i].pan);
				break;
			case 3:
				hide_panel(_baloon.BANANAS_3[i].pan);
				break;
			case 4:
				hide_panel(_baloon.BANANAS_4[i].pan);
				break;
		}
	}

	for (int i = 0; i < _baloon.fuelLen[_baloon.location]; i++)
	{
		switch (_baloon.location)
		{
			case 0:
				hide_panel(_baloon.FUELS_0[i].pan);
				break;
			case 1:
				hide_panel(_baloon.FUELS_1[i].pan);
				break;	
			case 2:
				hide_panel(_baloon.FUELS_2[i].pan);
				break;
			case 3:
				hide_panel(_baloon.FUELS_3[i].pan);
				break;
			case 4:
				hide_panel(_baloon.FUELS_4[i].pan);
				break;
		}
	}

	_baloon.choice = 0;
	show_panel(_baloon.MENU[_baloon.choice].pan);
	update_panels();
	doupdate();
	
	navigate(_baloon);

	
	//update_panels();
	//doupdate();
	//_baloon.choice = 0;
	//navigate(_baloon);
}
