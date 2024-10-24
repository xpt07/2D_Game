#pragma once
#include "GamesEngineeringBase.h"

using namespace GamesEngineeringBase;

class BackgroundTiles
{
public:
	BackgroundTiles();
	void draw(Window& window);
private:
	Image tiles[6];
};