#pragma once
#include "GamesEngineeringBase.h"
#include "vec2.h"

using namespace GamesEngineeringBase;

class Shape
{
public:
	virtual bool inside(vec2 p) = 0;
	virtual float area() = 0;
	virtual void draw(Window& window) = 0;
private:

};