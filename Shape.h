#pragma once
#include "core.h"

using namespace GamesEngineeringBase;

class Shape
{
public:
	virtual bool inside(vec2 p) = 0;
	virtual float area() = 0;
	virtual void draw(Window& window) = 0;

private:
	float radius;
};