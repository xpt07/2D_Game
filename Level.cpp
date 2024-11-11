#include "Level.h"
#include <cmath>
#include <cstdlib>

Level::Level(int waveNumber, float waveRadius, int enemiesPerWave, LevelType type)
    : waveNumber(waveNumber), waveRadius(waveRadius), enemiesPerWave(enemiesPerWave), currentLevelType(type) {}

void Level::spawnEnemies(std::vector<std::unique_ptr<GameObject>>& enemies, vec2 playerPos) {
    // Same enemy spawning logic as before
    float randomAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * 3.14159f;
    vec2 spawnPos = vec2(
        playerPos.x + waveRadius * std::cos(randomAngle),
        playerPos.y + waveRadius * std::sin(randomAngle)
    );

    if (rand() % 2 == 0) {
        enemies.push_back(std::make_unique<KamikazeEnemy>(spawnPos));
    }
    else {
        enemies.push_back(std::make_unique<BomberEnemy>(spawnPos, 200));
    }
}
