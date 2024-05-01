#ifndef _ENEMY_H
#define _ENEMY_H

#include "Monkey.h"

class Enemy: public Monkey
{
private:
	int reward;
	double delay;
public :
	Enemy(int _y, int _x, int _h, int _w);
	~Enemy();

	void setDelay(int _idx = 0);
};

#endif // _ENEMY_H
