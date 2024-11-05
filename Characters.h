#pragma once
#include "vec2.h"
#include "GamesEngineeringBase.h"

using namespace std;
using namespace GamesEngineeringBase;

class Characters
{
public:
	Characters(string sImage, vec2 startPos);
	virtual ~Characters() = default;
	virtual void onUpdate(Window& window) = 0;
	void draw(Window& w);
	vec2 getPos() { return pos; }

protected:
	Image image;
	vec2 pos;
};
