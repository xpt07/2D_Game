#include "Level.h"
#include <cmath>
#include <cstdlib>

Level::Level(int waveNumber, float waveRadius, int enemiesPerWave, LevelType type)
    : waveNumber(waveNumber), waveRadius(waveRadius), enemiesPerWave(enemiesPerWave), currentLevelType(type) {}

void Level::spawnEnemies(GameObject* enemies[], int& enemyCount, vec2 playerPos) {
    for (int i = 0; i < enemiesPerWave && enemyCount < MAX_ENEMIES; ++i) {
        float randomAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2 * 3.14159f;
        vec2 spawnPos = vec2(
            playerPos.x + waveRadius * std::cos(randomAngle),
            playerPos.y + waveRadius * std::sin(randomAngle)
        );

        int enemyType = rand() % 4;

        switch (enemyType) {
        case 0:
            enemies[enemyCount++] = new KamikazeEnemy(spawnPos);
            break;
        case 1:
            enemies[enemyCount++] = new BomberEnemy(spawnPos, 200);
            break;
        case 2:
            enemies[enemyCount++] = new DestroyerEnemy(spawnPos);
            break;
        case 3:
            enemies[enemyCount++] = new SniperEnemy(spawnPos);
            break;
        default:
            break;
        }
    }
}
