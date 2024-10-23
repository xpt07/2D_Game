#pragma once
#include <cmath>

class vec2
{
public:
	float x, y;

	vec2():
		x(0), y(0)
	{}

	vec2(float _x, float _y) :
		x(_x), y(_y)
	{}

	void setPos(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	vec2 getPos() { return vec2(x, y); }

	float getLength()
	{
		float res = sqrtf(this->x + this->y);
	}

private:
};