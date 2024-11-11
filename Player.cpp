#include "Player.h"
#include <cmath>

Player::Player() :
    GameObject("resources/mainShip.png", vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), ObjectType::Player),
    cooldownTimer(0.0f), aoeCooldownTimer(0.0f), fireRateMultiplier(1.0f), powerUpDuration(0.0f)
{}

void Player::onUpdate(Window& canvas, float deltaTime, Background& background, Camera& camera) {
    resetMovement();
    if (canvas.keyPressed('W')) movement.y -= PLAYER_SPEED;
    if (canvas.keyPressed('S')) movement.y += PLAYER_SPEED;
    if (canvas.keyPressed('A')) movement.x -= PLAYER_SPEED;
    if (canvas.keyPressed('D')) movement.x += PLAYER_SPEED;

    int i = image.width;

    vec2 newPosition = pos + movement;
    if (!background.IsInfiniteWorld()) {
        if (newPosition.x < 0.0f) newPosition.x = 0.0f;
        if (newPosition.x > GRID_WIDTH * TILE_WIDTH - image.width) newPosition.x = GRID_WIDTH * TILE_WIDTH - image.width;
        if (newPosition.y < 0.0f) newPosition.y = 0.0f;
        if (newPosition.y > GRID_HEIGHT * TILE_HEIGHT - image.height) newPosition.y = GRID_HEIGHT * TILE_HEIGHT - image.height;
    }

    if (!background.isPositionBlocked(newPosition, camera)) {
        pos = newPosition;
    }

    if (cooldownTimer > 0) cooldownTimer -= deltaTime * fireRateMultiplier;
    if (aoeCooldownTimer > 0) aoeCooldownTimer -= deltaTime;
    if (powerUpDuration > 0) {
        powerUpDuration -= deltaTime;
        if (powerUpDuration <= 0) fireRateMultiplier = 1.0f;
    }
}

void Player::shootAtNearestEnemy(GameObject* enemies[], int enemyCount, Projectile* projectiles[], int& projectileCount) {
    if (cooldownTimer > 0 || projectileCount >= MAX_PROJECTILES) return;

    float closestDistance = -1.0f;
    vec2 targetPos;
    bool foundEnemy = false;

    for (int i = 0; i < enemyCount; ++i) {
        float distance = std::sqrt(std::pow(pos.x - enemies[i]->getPosition().x, 2) + std::pow(pos.y - enemies[i]->getPosition().y, 2));
        if (closestDistance < 0 || distance < closestDistance) {
            closestDistance = distance;
            targetPos = enemies[i]->getPosition();
            foundEnemy = true;
        }
    }

    if (foundEnemy) {
        vec2 direction = targetPos - pos;
        float length = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
        if (length != 0) {
            direction.x /= length;
            direction.y /= length;
        }

        projectiles[projectileCount++] = new Projectile(vec2(pos.x + 25, pos.y), direction, ObjectType::Player);
        cooldownTimer = cooldownDuration;
    }
}

void Player::useAOEAttack(GameObject* enemies[], int enemyCount) {
    if (aoeCooldownTimer > 0) return;

    const int N = 3;
    // Sort enemies based on health
    for (int i = 0; i < enemyCount - 1; ++i) {
        for (int j = 0; j < enemyCount - i - 1; ++j) {
            if (enemies[j]->getHealth() < enemies[j + 1]->getHealth()) {
                std::swap(enemies[j], enemies[j + 1]);
            }
        }
    }

    for (int i = 0; i < N && i < enemyCount; ++i) {
        enemies[i]->takeDamage(50);
        std::cout << "AOE attack hit enemy with " << enemies[i]->getHealth() << " health!" << std::endl;
    }

    aoeCooldownTimer = aoeCooldownDuration;
}

void Player::collectPowerUp() {
    fireRateMultiplier = 10.0f;
    powerUpDuration = 5.0f;
}

void Player::takeDamage(int amount) {
    health -= amount;
    if (health <= 0) {
        health = 0;
        std::cout << "Player has been destroyed!" << std::endl;
    }
    else {
        std::cout << "Player took damage! Current health: " << health << std::endl;
    }
}
