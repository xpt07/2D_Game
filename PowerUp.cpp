#include "PowerUp.h"

PowerUp::PowerUp(vec2 startPos) :
	GameObject(startPos, ObjectType::PowerUp), collected(false) {}

void PowerUp::draw(Window& window, const vec2& cameraOffset)
{
    vec2 screenPos = pos - cameraOffset;

    hitbox = std::make_unique<Circle>(
        vec2(screenPos.x, screenPos.y),
        1
    );

    // Draw the small green square (power-up)
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            int drawX = static_cast<int>(screenPos.x + i);
            int drawY = static_cast<int>(screenPos.y + j);
            if (drawX >= 0 && drawX < static_cast<int>(window.getWidth()) &&
                drawY >= 0 && drawY < static_cast<int>(window.getHeight())) {
                window.draw(drawX, drawY, 0, 255, 0);  // Draw green square
            }
        }
    }
}
