#pragma once
#include "Characters.h"

class Player : public Characters
{
public:
	Player(string sImage);

	void onUpdate() override;

private:
	unsigned int planeX = window.getWidth() / 2 - (image.width / 2);
	unsigned int planeY = window.getHeight() / 2 - (image.height / 2);
};

