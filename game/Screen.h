#ifndef _SCREEN_H
#define _SCREEN_H

#include "Monkey.h"
#include <string>

class Screen: public Monkey
{
public:
	std::string path;

	Screen();
	Screen(int _y, int _x, int _h, int _w, std::string _filename);
};

#endif // _SCREEN_H
