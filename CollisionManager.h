#pragma once
#include "Player.h"
#include "Projectile.h"
#include <vector>
#include <cmath>
#include <algorithm>  // For std::remove_if

class CollisionManager {
public:
    static void checkCollisions(Player* player,
        std::vector<std::unique_ptr<GameObject>>& enemies,
        std::vector<std::unique_ptr<Projectile>>& projectiles) {

        // Check for collisions between projectiles and enemies
        projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
            [&enemies](const std::unique_ptr<Projectile>& projectile) {
                bool shouldRemoveProjectile = false;

                // Use an iterator to iterate and remove enemies
                enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                    [&projectile, &shouldRemoveProjectile](const std::unique_ptr<GameObject>& enemy) {
                        Circle* enemyHitbox = dynamic_cast<Circle*>(enemy->getHitbox());
                        Circle* projectileHitbox = dynamic_cast<Circle*>(projectile->getHitbox());

                        if (enemyHitbox && projectileHitbox) {
                            float distance = std::sqrt(
                                std::pow(enemyHitbox->getCenter().x - projectileHitbox->getCenter().x, 2) +
                                std::pow(enemyHitbox->getCenter().y - projectileHitbox->getCenter().y, 2)
                            );

                            if (distance <= enemyHitbox->getRadius() + projectileHitbox->getRadius()) {
                                shouldRemoveProjectile = true;  // Mark the projectile for removal
                                return true;  // Mark the enemy for removal
                            }
                        }
                        return false;  // Keep the enemy if no collision
                    }),
                    enemies.end());

                return shouldRemoveProjectile;  // Remove the projectile if it hit an enemy
            }),
            projectiles.end());

        // Check for collisions between player and enemies
        Circle* playerHitbox = dynamic_cast<Circle*>(player->getHitbox());
        if (!playerHitbox) return;

        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [player, playerHitbox](const std::unique_ptr<GameObject>& enemy) {
                Circle* enemyHitbox = dynamic_cast<Circle*>(enemy->getHitbox());
                if (enemyHitbox) {
                    float distance = std::sqrt(
                        std::pow(playerHitbox->getCenter().x - enemyHitbox->getCenter().x, 2) +
                        std::pow(playerHitbox->getCenter().y - enemyHitbox->getCenter().y, 2)
                    );

                    if (distance <= playerHitbox->getRadius() + enemyHitbox->getRadius()) {
                        if (enemy->getCharacterType() == ObjectType::Kamikaze) {
                            player->takeDamage(10);  // Damage from Kamikaze
                            return true;   // Mark this enemy for removal
                        }
                    }
                }
                return false;  // Keep the enemy if no collision
            }),
            enemies.end());
    }
};
