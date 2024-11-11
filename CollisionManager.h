#pragma once
#include "Player.h"
#include "Projectile.h"
#include "PowerUp.h"
#include <cmath>

/// Class responsible for managing collisions between game objects such as the player, enemies, projectiles, and power-ups
class CollisionManager {
public:
    /**
     * @brief Checks for and handles collisions between the player, enemies, projectiles, and power-ups.
     *
     * @param player Pointer to the player object
     * @param enemies Array of pointers to enemy game objects
     * @param enemyCount Number of enemies in the array
     * @param projectiles Array of pointers to projectile objects
     * @param projectileCount Number of projectiles in the array
     * @param powerUps Array of pointers to power-up objects
     * @param powerUpCount Number of power-ups in the array
     * @param camera The camera object to determine the game view boundaries
     * @param enemiesDefeated Reference to the count of enemies defeated by the player
     */
    static void checkCollisions(Player* player,
        GameObject* enemies[], int& enemyCount,
        Projectile* projectiles[], int& projectileCount,
        PowerUp* powerUps[], int& powerUpCount,
        const Camera& camera,
        int& enemiesDefeated) {

        handleProjectileEnemyCollisions(enemies, enemyCount, projectiles, projectileCount, enemiesDefeated);
        handlePlayerProjectileCollisions(player, projectiles, projectileCount);
        removeOffScreenProjectiles(projectiles, projectileCount, camera);
        handlePlayerPowerUpCollisions(player, powerUps, powerUpCount);
        handlePlayerEnemyCollisions(player, enemies, enemyCount);
    }

private:
    /**
     * @brief Handles collisions between the player and power-ups.
     *
     * @param player Pointer to the player object
     * @param powerUps Array of pointers to power-up objects
     * @param powerUpCount Number of power-ups in the array
     */
    static void handlePlayerPowerUpCollisions(Player* player, PowerUp* powerUps[], int& powerUpCount) {
        for (int i = 0; i < powerUpCount; ++i) {
            if (checkCollision(player, powerUps[i])) {
                player->collectPowerUp();
                removePowerUp(i, powerUps, powerUpCount);
            }
        }
    }

    /**
     * @brief Handles collisions between projectiles and enemies, and manages enemy defeat and projectile removal.
     *
     * @param enemies Array of pointers to enemy game objects
     * @param enemyCount Number of enemies in the array
     * @param projectiles Array of pointers to projectile objects
     * @param projectileCount Number of projectiles in the array
     * @param enemiesDefeated Reference to the count of enemies defeated by the player
     */
    static void handleProjectileEnemyCollisions(GameObject* enemies[], int& enemyCount,
        Projectile* projectiles[], int& projectileCount, int& enemiesDefeated) {

        for (int i = 0; i < projectileCount; ++i) {
            bool shouldRemoveProjectile = false;
            for (int j = 0; j < enemyCount; ++j) {
                if (enemies[j]->getCharacterType() == projectiles[i]->getOriginType()) continue;
                if (checkCollision(projectiles[i], enemies[j])) {
                    shouldRemoveProjectile = true;
                    enemies[j]->takeDamage(100);
                    if (enemies[j]->getHealth() <= 0) ++enemiesDefeated;
                }
            }
            if (shouldRemoveProjectile) removeProjectile(i, projectiles, projectileCount);
        }
    }

    /**
     * @brief Handles collisions between the player and enemy projectiles, applying damage to the player and removing projectiles.
     *
     * @param player Pointer to the player object
     * @param projectiles Array of pointers to projectile objects
     * @param projectileCount Number of projectiles in the array
     */
    static void handlePlayerProjectileCollisions(Player* player, Projectile* projectiles[], int& projectileCount) {
        for (int i = 0; i < projectileCount; ++i) {
            if (projectiles[i]->getOriginType() != ObjectType::Player && checkCollision(player, projectiles[i])) {
                player->takeDamage(5);
                removeProjectile(i, projectiles, projectileCount);
            }
        }
    }

    /**
     * @brief Handles collisions between the player and enemies, applying damage to both if necessary.
     *
     * @param player Pointer to the player object
     * @param enemies Array of pointers to enemy game objects
     * @param enemyCount Number of enemies in the array
     */
    static void handlePlayerEnemyCollisions(Player* player, GameObject* enemies[], int& enemyCount) {
        for (int i = 0; i < enemyCount; ++i) {
            if (checkCollision(player, enemies[i])) {
                if (enemies[i]->getCharacterType() == ObjectType::Kamikaze) {
                    player->takeDamage(10);
                    enemies[i]->takeDamage(100);
                }
            }
        }
    }

    /**
     * @brief Checks for a collision between two game objects using their hitboxes.
     *
     * @param obj1 Pointer to the first game object
     * @param obj2 Pointer to the second game object
     * @return true if a collision is detected, false otherwise
     */
    static bool checkCollision(GameObject* obj1, GameObject* obj2) {
        Circle* hitbox1 = dynamic_cast<Circle*>(obj1->getHitbox());
        Circle* hitbox2 = dynamic_cast<Circle*>(obj2->getHitbox());

        if (hitbox1 && hitbox2) {
            float distance = std::sqrt(
                std::pow(hitbox1->getCenter().x - hitbox2->getCenter().x, 2) +
                std::pow(hitbox1->getCenter().y - hitbox2->getCenter().y, 2)
            );
            return distance <= (hitbox1->getRadius() + hitbox2->getRadius());
        }
        return false;
    }

    /**
     * @brief Removes projectiles that are off-screen and outside the extended game boundary.
     *
     * @param projectiles Array of pointers to projectile objects
     * @param projectileCount Number of projectiles in the array
     * @param camera The camera object to determine the game view boundaries
     */
    static void removeOffScreenProjectiles(Projectile* projectiles[], int& projectileCount, const Camera& camera) {
        vec2 cameraPos = camera.getPosition();
        float extendedBoundary = 200.0f;
        float screenWidth = WINDOW_WIDTH + extendedBoundary;
        float screenHeight = WINDOW_HEIGHT + extendedBoundary;

        for (int i = 0; i < projectileCount; ++i) {
            vec2 pos = projectiles[i]->getPosition();
            if (pos.x < cameraPos.x - screenWidth / 2 - extendedBoundary ||
                pos.x > cameraPos.x + screenWidth / 2 + extendedBoundary ||
                pos.y < cameraPos.y - screenHeight / 2 - extendedBoundary ||
                pos.y > cameraPos.y + screenHeight / 2 + extendedBoundary) {
                removeProjectile(i, projectiles, projectileCount);
            }
        }
    }

    /**
     * @brief Removes a projectile from the array and updates the projectile count.
     *
     * @param index Index of the projectile to remove
     * @param projectiles Array of pointers to projectile objects
     * @param projectileCount Number of projectiles in the array
     */
    static void removeProjectile(int index, Projectile* projectiles[], int& projectileCount) {
        delete projectiles[index];
        projectiles[index] = projectiles[--projectileCount];
    }

    /**
     * @brief Removes a power-up from the array and updates the power-up count.
     *
     * @param index Index of the power-up to remove
     * @param powerUps Array of pointers to power-up objects
     * @param powerUpCount Number of power-ups in the array
     */
    static void removePowerUp(int index, PowerUp* powerUps[], int& powerUpCount) {
        delete powerUps[index];
        powerUps[index] = powerUps[--powerUpCount];
    }
};
