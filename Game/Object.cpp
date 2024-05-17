#include "Object.h"

using namespace std;

Object::Object(int _y, int _x, int _h, int _w, string _filename): Screen(_y, _x, _h, _w, _filename), reward{100}, delay{0}
{}

