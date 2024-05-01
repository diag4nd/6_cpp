#ifndef _SCREEN_H
#define _SCREEN_H

#include "Monkey.h"
#include <string>

using namespace std;

class Screen: public Monkey
{
public:
	Screen();
	Screen(int _y, int _x, int _h, int _w, string _filename);

	string path;
};

#endif // _SCREEN_H
