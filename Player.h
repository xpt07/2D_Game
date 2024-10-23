#pragma once
#include "Characters.h"

class Player : public Characters
{
public:
	Player(string sImage, vec2 startPos);
	void onUpdate(GamesEngineeringBase::Window& window) override;
	Image getImage() { return playerImage; }
	vec2 getPos() { return playerPos; }
private:
	Image playerImage;
	vec2 playerPos;
	bool withinBounds(int x, int y, int width, int height);
};

