#pragma once
#include "GameObject.h"

/// @file Projectile.h
/// @brief Defines the Projectile class, which handles the behavior of projectiles fired by the player or enemies.

/// @class Projectile
/// @brief Represents a moving projectile in the game world.
class Projectile : public GameObject {
public:
    /**
     * @brief Constructs a Projectile object with a starting position, direction, and shooter type.
     * @param startPos The initial position of the projectile.
     * @param _direction The direction in which the projectile moves.
     * @param _shooterType The type of the object that fired the projectile (e.g., Player, Enemy).
     */
    Projectile(vec2 startPos, vec2 _direction, ObjectType _shooterType) :
        GameObject(startPos, ObjectType::Projectile), direction(_direction), speed(5.f), originType(_shooterType) {}

    /**
     * @brief Updates the position of the projectile based on its speed and direction.
     */
    void onUpdate() override {
        // Move the projectile in the specified direction
        pos.x += direction.x * speed;
        pos.y += direction.y * speed;
    }

    /**
     * @brief Draws the projectile on the canvas, applying the camera offset for proper positioning.
     * @param canvas The window to draw to.
     * @param cameraOffset The camera offset to apply when drawing.
     */
    void draw(Window& canvas, const vec2& cameraOffset) {
        vec2 screenPos = pos - cameraOffset;

        // Create a hitbox for the projectile
        hitbox = std::make_unique<Circle>(vec2(screenPos.x, screenPos.y), 1);

        // Draw the projectile as a small red square (5x5 pixels)
        for (unsigned int i = 0; i < 5; i++) {
            for (unsigned int j = 0; j < 5; j++) {
                int drawX = static_cast<int>(screenPos.x + i);
                int drawY = static_cast<int>(screenPos.y + j);

                // Only draw if within the window bounds
                if (drawX >= 0 && drawX < static_cast<int>(canvas.getWidth()) &&
                    drawY >= 0 && drawY < static_cast<int>(canvas.getHeight())) {

                    canvas.draw(drawX, drawY, 255, 0, 0); // Draw in red color
                }
            }
        }
    }

    /**
     * @brief Gets the type of the object that originated the projectile.
     * @return The origin type of the projectile.
     */
    ObjectType getOriginType() const { return originType; }

private:
    vec2 direction; ///< The direction in which the projectile moves.
    float speed; ///< The speed at which the projectile travels.
    ObjectType originType; ///< The type of the object that fired the projectile (e.g., Player, Enemy).
};
