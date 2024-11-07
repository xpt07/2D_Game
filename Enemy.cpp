#include "Enemy.h"
#include <cmath>

Enemy::Enemy(const std::string& sImage, vec2 startPos, EnemyType type) : 
    Characters(sImage, startPos), type(type), position(startPos)
{}

void Enemy::onUpdate(vec2 target) {
    vec2 direction = target - pos;

    float length = std::sqrt(pow(direction.x, 2) + pow(direction.y, 2));

    // Normalize the direction vector to unit length
    if (length != 0) {  // To prevent division by zero
        direction.x /= length;
        direction.y /= length;
    }

    // Move the enemy a small step in the direction of the player
    float speed = 2.0f;  // Adjust this value to control the speed of the enemy

    // Example behavior based on enemy type
    if (type == EnemyType::Kamikaze) {
        pos.x += direction.x * speed;
        pos.y += direction.y * speed;
    }
    else if (type == EnemyType::Bomber) {


    }

    // Update the position of the hitbox to stay aligned with the enemy
    if (Circle* circ = dynamic_cast<Circle*>(hitbox.get())) {
        circ->setCenter(vec2(pos.x + image.width / 2.0f, pos.y + image.height / 2.0f));
    }
}
