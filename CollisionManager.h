#pragma once
#include "Player.h"
#include "Projectile.h"
#include <vector>
#include <cmath>
#include <algorithm>

class CollisionManager {
public:
    static void checkCollisions(Player* player,
        std::vector<std::unique_ptr<GameObject>>& enemies,
        std::vector<std::unique_ptr<Projectile>>& projectiles,
        const Camera& camera,
        int& enemiesDefeated) {
        handleProjectileEnemyCollisions(enemies, projectiles, enemiesDefeated);
        removeOffScreenProjectiles(projectiles, camera);
        handlePlayerEnemyCollisions(player, enemies);
    }

private:
    // Function to handle collisions between projectiles and enemies
    static void handleProjectileEnemyCollisions(std::vector<std::unique_ptr<GameObject>>& enemies,
        std::vector<std::unique_ptr<Projectile>>& projectiles, 
        int& enemiesDefeated) {
        for (auto it = projectiles.begin(); it != projectiles.end(); ) {
            bool shouldRemoveProjectile = false;

            for (auto enemyIt = enemies.begin(); enemyIt != enemies.end(); ) {
                if ((*enemyIt)->getCharacterType() == (*it)->getOriginType()) {
                    ++enemyIt;  // Skip collision check if same type
                    continue;
                }

                if (checkCollision(it->get(), enemyIt->get())) {
                    shouldRemoveProjectile = true;
                    enemyIt = enemies.erase(enemyIt);  // Remove enemy
                    ++enemiesDefeated;
                }
                else {
                    ++enemyIt;
                }
            }

            if (shouldRemoveProjectile) {
                it = projectiles.erase(it);  // Remove projectile
            }
            else {
                ++it;
            }
        }
    }

    // Function to handle collisions between the player and enemies
    static void handlePlayerEnemyCollisions(Player* player, std::vector<std::unique_ptr<GameObject>>& enemies) {
        Circle* playerHitbox = dynamic_cast<Circle*>(player->getHitbox());
        if (!playerHitbox) return;

        for (auto it = enemies.begin(); it != enemies.end(); ) {
            if (checkCollision(player, it->get())) {
                if ((*it)->getCharacterType() == ObjectType::Kamikaze) {
                    player->takeDamage(10);  // Damage from Kamikaze
                    it = enemies.erase(it);  // Remove enemy
                    continue;
                }
            }
            ++it;
        }
    }

    // Function to check collision between two GameObjects
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

    // Function to remove off-screen projectiles based on the camera's position
    static void removeOffScreenProjectiles(std::vector<std::unique_ptr<Projectile>>& projectiles, const Camera& camera) {
        vec2 cameraPos = camera.getPosition();
        float extendedBoundary = 200.0f;  // Extend the boundary to prevent early deletion
        float screenWidth = WINDOW_WIDTH + extendedBoundary;
        float screenHeight = WINDOW_HEIGHT + extendedBoundary;

        for (auto it = projectiles.begin(); it != projectiles.end(); ) {
            vec2 pos = (*it)->getPosition();
            if (pos.x < cameraPos.x - screenWidth / 2 - extendedBoundary ||
                pos.x > cameraPos.x + screenWidth / 2 + extendedBoundary ||
                pos.y < cameraPos.y - screenHeight / 2 - extendedBoundary ||
                pos.y > cameraPos.y + screenHeight / 2 + extendedBoundary) {
                it = projectiles.erase(it);  // Remove projectile
            }
            else {
                ++it;
            }
        }
    }

    int enemiesDefeated = 0;
};
