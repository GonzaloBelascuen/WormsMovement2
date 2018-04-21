#include "position.h"



position::position()
{
	x = 0;
	y = 0;
}

position::position(double _x, double _y)
{
	x = _x;
	y = _y;
}


position::~position()
{
}

void position::setX(double _x)
{
	x = _x;
}

void position::setY(double _y)
{
	y = _y;
}

double position::getX()
{
	return x;
}

double position::getY()
{
	return y;
}
