#include "Monkey.h"

Monkey::Monkey()
{}

Monkey::Monkey(int _y, int _x, int _h, int _w): y{_y}, x{_x}, height{_h}, width{_w}
{
	win = newwin(height, width, y, x);
	pan = new_panel(win);
	refresh();
}

Monkey::~Monkey()
{
	del_panel(pan);
	delwin(win)
};
