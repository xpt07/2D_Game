#pragma once
#include "GamesEngineeringBase.h"

using namespace std;
using namespace GamesEngineeringBase;

class Characters
{
public:
	Characters(string sImage);
	virtual ~Characters() = default;
	virtual void onUpdate() = 0;
	void draw(Window& w);

protected:
	Image image;
	Window window;
	unsigned int planeX;
	unsigned int planeY;
};
