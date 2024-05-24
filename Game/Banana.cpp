#include "Banana.h"

using namespace std;

Banana::Banana()
{}

Banana::Banana(int _y, int _x, int _h, int _w, string _filename): Screen(_y, _x, _h, _w, _filename), reward(100), isActive(true)
{
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_YELLOW);
	wchgat(win, 1, A_NORMAL, 1, NULL);
}

