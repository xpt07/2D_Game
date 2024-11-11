#include "Enemy.h"
#include "Projectile.h"
#include <cmath>

Enemy::Enemy(const std::string& sImage, vec2 startPos, ObjectType type, int h, float _speed)
    : GameObject(sImage, startPos, type, h), speed(_speed) {}

Enemy::Enemy(const std::string& sImage, vec2 startPos, ObjectType type, float _speed)
    : GameObject(sImage, startPos, type), speed(_speed) {}

KamikazeEnemy::KamikazeEnemy(vec2 startPos)
    : Enemy("resources/kamikaze_plane_sprite.png", startPos, ObjectType::Kamikaze, 2.0f) {}

void KamikazeEnemy::onUpdate(vec2 target, float deltaTime) {
    if (health <= 0) return;
    vec2 direction = target - pos;
    float length = std::sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }
    pos.x += direction.x * speed;
    pos.y += direction.y * speed;
}

BomberEnemy::BomberEnemy(vec2 startPos, int h)
    : Enemy("resources/bomber_plane_sprite.png", startPos, ObjectType::Bomber, 1.5f) {}

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
    if (cooldownTimer > 0) {
        cooldownTimer -= deltaTime;
        return;
    }
}

void BomberEnemy::shootAtPlayer(vec2 playerPos, Projectile* projectiles[], int& projectileCount) {
    if (cooldownTimer > 0 || projectileCount >= MAX_PROJECTILES) return;
    vec2 direction = playerPos - pos;
    float length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }
    projectiles[projectileCount++] = new Projectile(vec2(pos.x, pos.y), direction, ObjectType::Bomber);
    cooldownTimer = cooldownDuration;
}

DestroyerEnemy::DestroyerEnemy(vec2 startPos)
    : Enemy("resources/destroyer_sprite.png", startPos, ObjectType::Destroyer, 10000, 1.0f) {}

void DestroyerEnemy::onUpdate(vec2 target, float deltaTime) {
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
}

void DestroyerEnemy::explodeAndShoot(vec2 playerPos, Projectile* projectiles[], int& projectileCount) {
    if (projectileCount >= MAX_PROJECTILES - 3) return;
    vec2 direction = playerPos - pos;
    float length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }
    projectiles[projectileCount++] = new Projectile(vec2(pos.x, pos.y - 20), direction, ObjectType::Destroyer);
    projectiles[projectileCount++] = new Projectile(vec2(pos.x, pos.y), direction, ObjectType::Destroyer);
    projectiles[projectileCount++] = new Projectile(vec2(pos.x, pos.y + 20), direction, ObjectType::Destroyer);
    health = 0;
}

SniperEnemy::SniperEnemy(vec2 startPos)
    : Enemy("resources/sniper_sprite.png", startPos, ObjectType::Sniper, 100, 0.5f), cooldownTimer(3.0f) {}

void SniperEnemy::onUpdate(vec2 target, float deltaTime) {
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
    if (cooldownTimer > 0) {
        cooldownTimer -= deltaTime;
        return;
    }
}

void SniperEnemy::shootAtPlayer(vec2 playerPos, Projectile* projectiles[], int& projectileCount) {
    if (cooldownTimer > 0 || projectileCount >= MAX_PROJECTILES) return;
    vec2 direction = playerPos - pos;
    float length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }
    projectiles[projectileCount++] = new Projectile(vec2(pos.x, pos.y), direction, ObjectType::Sniper);
    cooldownTimer = cooldownDuration;
}
