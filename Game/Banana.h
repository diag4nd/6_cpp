#ifndef __BANANA_H__
#define __BANANA_H__

#include "Screen.h"

using namespace std;

class Banana: public Screen
{
public :
	Banana();
	Banana(int _y, int _x, int _h, int _w, string _filename);
	
	bool isActive;
	int reward;
};

#endif // __BANANA_H__
