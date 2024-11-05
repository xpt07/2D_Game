#pragma once
#include "Characters.h"

class Player : public Characters
{
public:
	Player(vec2 startPos);
	void onUpdate(GamesEngineeringBase::Window& window) override;
private:
	string playerImage;
};

