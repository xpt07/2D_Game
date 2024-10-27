#pragma once
#include <iostream>
#include "GamesEngineeringBase.h"
#include "Camera.h"

#define MAX_TILES 6

using namespace GamesEngineeringBase;

class Background
{
public:
	Background();

	void draw(Window& canvas, const Camera& camera);

private:
	Image tiles[MAX_TILES];
	int tileWidth, tileHeight;
	float scaleFactor = 2;
};