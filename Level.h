#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <memory>

class Level {
public:
	Level(int _waveNumber, float _waveRadius, int _enemiesPerWave);
	void spawnEnemies(std::vector<std::unique_ptr<GameObject>>& enemies, vec2 playerPos);

private:
	int waveNumber;
	float waveRadius;
	int enemiesPerWave;
};