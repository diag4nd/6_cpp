#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Screen.h"

using namespace std;

class Object: public Screen
{
private:
	int reward;
	double delay;
public :
	Object(int _y, int _x, int _h, int _w, string _filename);
	~Object();

	//void setDelay(int _idx = 0);
};

#endif // __OBJECT_H__
