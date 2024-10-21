#pragma once
#include "Characters.h"

class Player : public Characters
{
public:
	Player(string sImage, unsigned int startX, unsigned int startY);
	void onUpdate() override;
	Image getImage() { return playerImage; };
private:
	Image playerImage;
	unsigned int playerX, playerY;
};

