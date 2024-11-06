#include "Enemy.h"

Enemy::Enemy(const std::string& sImage, vec2 startPos, EnemyType type) : 
    Characters(sImage, startPos), type(type), position(startPos)
{}

void Enemy::onUpdate() {
    // Example behavior based on enemy type
    if (type == EnemyType::Kamikaze) {
        // Kamikaze enemies move toward the player (example logic)
        pos.y += 1;  // Move downwards; modify as needed
    }
    else if (type == EnemyType::Bomber) {
        // Bomber enemies might hover or drop bombs (example logic)
        pos.x += 0.5f;  // Slow sideways movement; modify as needed
    }

    // Update the position of the hitbox to stay aligned with the enemy
    if (Circle* circ = dynamic_cast<Circle*>(hitbox.get())) {
        circ->setCenter(vec2(pos.x + image.width / 2.0f, pos.y + image.height / 2.0f));
    }
}