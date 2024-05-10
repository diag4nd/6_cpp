#ifndef __MONKEY_H__
#define __MONKEY_H__

#include <panel.h>

class Monkey
{
public:
	Monkey();
	Monkey(int _y, int _x, int _h, int _w);
	~Monkey();

	WINDOW* win;
	PANEL* pan;
	int height, width;
	int y, x;
};

#endif // __MONKEY_H__
