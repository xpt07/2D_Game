#pragma once
#include "Shape.h"
#include <cmath>

class Circle : public Shape
{
public:
	Circle(vec2 c, float r):
		centre(c), radius(r)
	{}

	bool inside(vec2 p) override {

	}

	float area() override {
		return 3.14159f * radius * radius;
	}

private:
	vec2 centre;
	float radius
};