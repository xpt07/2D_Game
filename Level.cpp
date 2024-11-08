#include "Level.h"
#include <cmath>
#include <cstdlib>

Level::Level(int waveNumber, float waveRadius, int enemiesPerWave)
    : waveNumber(waveNumber), waveRadius(waveRadius), enemiesPerWave(enemiesPerWave) {}

void Level::spawnEnemies(std::vector<std::unique_ptr<GameObject>>& enemies, vec2 playerPos) {
    // Generate a random angle between 0 and 2*PI
    float randomAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * 3.14159f;

    // Calculate the spawn position along the radius
    vec2 spawnPos = vec2(
        playerPos.x + waveRadius * std::cos(randomAngle),
        playerPos.y + waveRadius * std::sin(randomAngle)
    );

    // Randomly decide whether to spawn a KamikazeEnemy or a BomberEnemy
    if (rand() % 2 == 0) {
        // Spawn a KamikazeEnemy
        enemies.push_back(std::make_unique<KamikazeEnemy>(spawnPos));
    }
    else {
        // Spawn a BomberEnemy
        enemies.push_back(std::make_unique<BomberEnemy>(spawnPos));
    }
}
