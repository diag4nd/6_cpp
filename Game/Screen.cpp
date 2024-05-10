#include "Screen.h"
#include "Monkey.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

Screen::Screen()
{}

Screen::Screen(int _y, int _x, int _h, int _w, string _filename): Monkey(_y, _x, _h, _w), path{".game/sprites/" + _filename}
{
	ifstream fRead;
	string line;
	int idx = 0;
	fRead.open(path.c_str());
	while (getline(fRead, line))
	{
		mvwprintw(win, idx, 0, line.c_str());
		idx++;
	}
	fRead.close();
}
