#pragma once
#include "Player.h"
#include "Enemy.h"

enum class LevelType {
    FixedBoundary,
    InfiniteWorld
};

class Level {
public:
    Level(int _waveNumber, float _waveRadius, int _enemiesPerWave, LevelType type);
    void spawnEnemies(GameObject* enemies[], int& enemyCount, vec2 playerPos);
    LevelType getLevelType() const { return currentLevelType; }
    void setLevelType(LevelType type) { currentLevelType = type; }

private:
    int waveNumber;
    float waveRadius;
    int enemiesPerWave;
    LevelType currentLevelType;
};
