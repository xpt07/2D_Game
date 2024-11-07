#pragma once
#include <iostream>
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

	vec2 operator+(const vec2& v) const
	{
		return vec2(x + v.x, y + v.y);
	}

	vec2 operator-(const vec2& v) const
	{
		return vec2(x - v.x, y - v.y);
	}

	vec2 operator/(const float value) const
	{
		if (value != 0) {
			return vec2(x / value, y / value);
		}
		else {
			std::cerr << "Attempt to divide by zero." << std::endl;
			return *this; // Return the original vector if divide by zero
		}
	}

	vec2 operator*(const float value) const
	{
		return vec2(x * value, y * value);
	}

	void operator+=(const vec2& v)
	{
		x += v.x;
		y += v.y;
	}

	void operator-=(const vec2& v)
	{
		x -= v.x;
		y -= v.y;
	}

private:
};