#include "GameObject.h"

GameObject::GameObject(const std::string& sImage, vec2 startPos, ObjectType type, int h) :
    pos(startPos), charType(type), health(h)
{
    image.load(sImage);
}

void GameObject::takeDamage(int amount)
{
    health -= amount;
    if (health < 0) {
        health = 0;
    }
}

void GameObject::draw(Window& window, const vec2& cameraOffset) {
    vec2 screenPos = pos - cameraOffset;

    hitbox = std::make_unique<Circle>(
        vec2(screenPos.x + image.width / 2.0f, screenPos.y + image.height / 2.0f),
        image.height / 1.5f
    );

    for (unsigned int i = 0; i < image.width; i++) {
        for (unsigned int j = 0; j < image.height; j++) {
            // Ensure the pixel is within the window bounds
            int drawX = static_cast<int>(screenPos.x + i);
            int drawY = static_cast<int>(screenPos.y + j);
    
            if (drawX >= 0 && drawX < static_cast<int>(window.getWidth()) &&
                drawY >= 0 && drawY < static_cast<int>(window.getHeight())) {
                if (image.alphaAt(i, j) > 200) {
                    window.draw(drawX, drawY, image.at(i, j));
                }
            }
        }
    }
}
