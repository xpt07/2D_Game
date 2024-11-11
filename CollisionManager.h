#pragma once
#include "Player.h"
#include "Projectile.h"
#include "PowerUp.h"
#include <vector>
#include <cmath>
#include <algorithm>

class CollisionManager {
public:
    static void checkCollisions(Player* player,
        std::vector<std::unique_ptr<GameObject>>& enemies,
        std::vector<std::unique_ptr<Projectile>>& projectiles,
        std::vector<std::unique_ptr<PowerUp>>& powerUps,
        const Camera& camera,
        int& enemiesDefeated) {
        handleProjectileEnemyCollisions(enemies, projectiles, enemiesDefeated);
        handlePlayerProjectileCollisions(player, projectiles);  // New method call
        removeOffScreenProjectiles(projectiles, camera);
        handlePlayerPowerUpCollisions(player, powerUps);
        handlePlayerEnemyCollisions(player, enemies);
    }

private:

    static void handlePlayerPowerUpCollisions(Player* player, std::vector<std::unique_ptr<PowerUp>>& powerUps) {
        for (auto it = powerUps.begin(); it != powerUps.end(); ) {
            if (checkCollision(player, it->get())) {
                player->collectPowerUp();  // Player collects the PowerUp
                it = powerUps.erase(it);   // Remove the PowerUp from the game
            }
            else {
                ++it;
            }
        }
    }

    static void handleProjectileEnemyCollisions(std::vector<std::unique_ptr<GameObject>>& enemies,
        std::vector<std::unique_ptr<Projectile>>& projectiles, int& enemiesDefeated) {
        for (auto it = projectiles.begin(); it != projectiles.end(); ) {
            bool shouldRemoveProjectile = false;

            for (auto& enemy : enemies) {
                if (enemy->getCharacterType() == (*it)->getOriginType()) continue;
                if (checkCollision(it->get(), enemy.get())) {
                    shouldRemoveProjectile = true;
                    enemy->takeDamage(100);  // Apply damage
                    if (enemy->getHealth() <= 0) ++enemiesDefeated;
                }
            }

            if (shouldRemoveProjectile) {
                it = projectiles.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    // New method to handle collisions between the player and enemy projectiles
    static void handlePlayerProjectileCollisions(Player* player, std::vector<std::unique_ptr<Projectile>>& projectiles) {
        for (auto it = projectiles.begin(); it != projectiles.end(); ) {
            if ((*it)->getOriginType() != ObjectType::Player && checkCollision(player, it->get())) {
                player->takeDamage(5);  // Player takes 5 points of damage
                it = projectiles.erase(it);  // Remove the projectile
            }
            else {
                ++it;
            }
        }
    }

    static void handlePlayerEnemyCollisions(Player* player, std::vector<std::unique_ptr<GameObject>>& enemies) {
        Circle* playerHitbox = dynamic_cast<Circle*>(player->getHitbox());
        if (!playerHitbox) return;

        for (auto& enemy : enemies) {
            if (checkCollision(player, enemy.get())) {
                if (enemy->getCharacterType() == ObjectType::Kamikaze) {
                    player->takeDamage(10);  // Apply damage
                    enemy->takeDamage(100);
                }
            }
        }
    }

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

    static void removeOffScreenProjectiles(std::vector<std::unique_ptr<Projectile>>& projectiles, const Camera& camera) {
        vec2 cameraPos = camera.getPosition();
        float extendedBoundary = 200.0f;
        float screenWidth = WINDOW_WIDTH + extendedBoundary;
        float screenHeight = WINDOW_HEIGHT + extendedBoundary;

        for (auto it = projectiles.begin(); it != projectiles.end(); ) {
            vec2 pos = (*it)->getPosition();
            if (pos.x < cameraPos.x - screenWidth / 2 - extendedBoundary ||
                pos.x > cameraPos.x + screenWidth / 2 + extendedBoundary ||
                pos.y < cameraPos.y - screenHeight / 2 - extendedBoundary ||
                pos.y > cameraPos.y + screenHeight / 2 + extendedBoundary) {
                it = projectiles.erase(it);
            }
            else {
                ++it;
            }
        }
    }
};
