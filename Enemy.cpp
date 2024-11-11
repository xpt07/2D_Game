#include "Enemy.h"
#include "Projectile.h"
#include <cmath>

Enemy::Enemy(const std::string& sImage, vec2 startPos, ObjectType type, int h, float _speed) :
    GameObject(sImage, startPos, type, h), speed(_speed)
{}

Enemy::Enemy(const std::string& sImage, vec2 startPos, ObjectType type, float _speed) :
    GameObject(sImage, startPos, type), speed(_speed)
{}

KamikazeEnemy::KamikazeEnemy(vec2 startPos) 
    : Enemy("resources/kamikaze_plane_sprite.png", startPos, ObjectType::Kamikaze, 2.0f) {}

void KamikazeEnemy::onUpdate(vec2 target, float deltaTime) {
    if (health <= 0) return;
    
    vec2 direction = target - pos;
    float length = std::sqrt(pow(direction.x, 2) + pow(direction.y, 2));

    if (length != 0) {
        // Normalize the direction vector
        direction.x /= length;
        direction.y /= length;
    }
    pos.x += direction.x * speed;
    pos.y += direction.y * speed;
}

BomberEnemy::BomberEnemy(vec2 startPos, int h) :
    Enemy("resources/bomber_plane_sprite.png", startPos, ObjectType::Bomber, 1.5f) {}

void BomberEnemy::onUpdate(vec2 target, float deltaTime) {
    if (health <= 0) return;
    
    vec2 direction = target - pos;
    float length = std::sqrt(pow(direction.x, 2) + pow(direction.y, 2));

    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }

    if (length > attackDistance) {
        pos.x += direction.x * speed;
        pos.y += direction.y * speed;
    }

    // Only shoot if the cooldown timer has expired
    if (cooldownTimer > 0) {
        cooldownTimer -= deltaTime;  // Decrease cooldown timer (assuming ~60 FPS, so 1 frame ~ 0.016s)
        return;
    }
}

void BomberEnemy::shootAtPlayer(vec2 playerPos, std::vector<std::unique_ptr<Projectile>>& projectiles)
{
    if (cooldownTimer > 0) return;

    // Calculate the direction to the player
    vec2 direction = playerPos - pos;
    float length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }

    // Create a projectile aimed at the player
    projectiles.push_back(std::make_unique<Projectile>(vec2(pos.x, pos.y), direction, ObjectType::Bomber));

    // Reset the cooldown timer
    cooldownTimer = cooldownDuration;
}