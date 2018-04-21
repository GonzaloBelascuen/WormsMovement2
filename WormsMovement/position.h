#pragma once
class position
{
private:

	double x;
	double y;

public:

	position();
	position(double _x, double _y);
	~position();

	void setX(double _x);
	void setY(double _y);
	double getX();
	double getY();
};

