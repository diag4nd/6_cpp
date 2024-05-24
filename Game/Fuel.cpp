#include "Fuel.h"

using namespace std;

Fuel::Fuel()
{}

Fuel::Fuel(int _y, int _x, int _h, int _w, string _filename): Screen(_y, _x, _h, _w, _filename), isActive(true)
{
	start_color();
	init_pair(2, COLOR_BLACK, COLOR_GREEN);
	wchgat(win, 1, A_NORMAL, 2, NULL);
}

