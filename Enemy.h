#pragma once
#include "Characters.h"

enum class missiles{ playerRay = 0, EnergyBall, };

class Missile : public Characters
{
public:
	Missile(vec2 spawnPos, string missileImage) : Characters(missileImage, spawnPos)
	{
		spawnPos = vec2((1024 / 2), (2 * 768 / 3));
	}

	void onUpdate(GamesEngineeringBase::Window& window) override {

	}

private:
};

