#include "Screen.h"
#include <fstream>

Screen::Screen()
{}

Screen::Screen(int _y, int _x, int _h, int _w, std::String _filename)
{
	std::ifstream fRead;
	std::string line;
	int idx = 0;
	
	fRead.open(path.c_str());
	while (std::getline(fRead, line))
	{
		mvwprintw(win, idx, 0, line.c_str());
	}
	fRead.close();
	wrefresh(win);
}
