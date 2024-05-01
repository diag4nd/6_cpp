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
					choice = 0;
					//showHelp();
					break;
				case 2:
					choice = 0;
					//showHallOfFame();
					break;
				case 3:
					endwin();
					return 0;
				case 4:
					return 1;
				case 7:
					choice = 0;
					hide_panel(_menu[_idx].pan);
					show_panel(_menu[choice].pan);
					update_panels();
					doupdate();
					navigate(choice, _menu);
			}
	}
}
/*
int play(Player _ballon)
{

}
*/
