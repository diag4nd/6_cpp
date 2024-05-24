#ifndef __FUEL_H__
#define __FUEL_H__

#include "Screen.h"

using namespace std;

class Fuel: public Screen
{
public :
	Fuel();
	Fuel(int _y, int _x, int _h, int _w, string _filename);
	
	bool isActive;
};

#endif // __FUEL_H__
