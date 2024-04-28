#ifndef _MONKEY_H
#define _MONKEY_H

#include <panel.h>

class Monkey
{
public:
	WINDOW* win;
	PANEL pan;
	int height, width;
	int y, x;

	bool isHitted();

	Monkey();
	Monkey(int _y, int _x, int _h, int _w);
	~Monkey();
};

#endif // _MONKEY_H
