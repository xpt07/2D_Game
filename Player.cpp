#include "Player.h" 

Player::Player():
	GameObject("resources/mainShip.png", vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), ObjectType::Player),
    cooldownTimer(0.0f)
{}

void Player::onUpdate(Window& canvas, float deltaTime, Background& background, Camera& camera)
{
    vec2 movement(0, 0);
    if (canvas.keyPressed('W')) movement.y -= PLAYER_SPEED;
    if (canvas.keyPressed('S')) movement.y += PLAYER_SPEED;
    if (canvas.keyPressed('A')) movement.x -= PLAYER_SPEED;
    if (canvas.keyPressed('D')) movement.x += PLAYER_SPEED;

    vec2 newPosition = pos + movement;

    if (!background.IsInfiniteWorld()) {  // Assuming isInfiniteWorld() is the method to check
        if (newPosition.x < 0.0f) newPosition.x = 0.0f;
        if (newPosition.x > GRID_WIDTH * TILE_WIDTH - image.width) newPosition.x = GRID_WIDTH * TILE_WIDTH - image.width;
        if (newPosition.y < 0.0f) newPosition.y = 0.0f;
        if (newPosition.y > GRID_HEIGHT * TILE_HEIGHT - image.height) newPosition.y = GRID_HEIGHT * TILE_HEIGHT - image.height;
    }

    if (!background.isPositionBlocked(newPosition, camera)) {
        pos = newPosition;
    }

    if (this->cooldownTimer > 0) {
        this->cooldownTimer -= deltaTime;
    }

}

void Player::shootAtNearestEnemy(std::vector<std::unique_ptr<GameObject>>& enemies, std::vector<std::unique_ptr<Projectile>>& projectiles)
{

    if (cooldownTimer > 0) return;

    float closestDistance = -1.0f;
    vec2 targetPos;
    bool foundEnemy = false;

    for (const auto& enemy : enemies) {
        float distance = std::sqrt(std::pow(pos.x - enemy->getPosition().x, 2) + std::pow(pos.y - enemy->getPosition().y, 2));

        if (closestDistance < 0 || distance < closestDistance) {
            closestDistance = distance;
            targetPos = enemy->getPosition();
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

        projectiles.push_back(std::make_unique<Projectile>(vec2(pos.x + 25, pos.y), direction, ObjectType::Player));

        cooldownTimer = cooldownDuration;
    }
}

void Player::takeDamage(int amount)
{
    health -= amount;
    if (health <= 0) {
        health = 0;
        std::cout << "Player has been destroyed!" << std::endl;

    }
    else {
        std::cout << "Player took damage! Current health: " << health << std::endl;
    }
}

