#include "Characters.h"

Characters::Characters(const std::string& sImage, vec2 startPos) :
    pos(startPos)
{
    image.load(sImage);
}

void Characters::draw(Window& window, const vec2& cameraOffset) {
    vec2 screenPos = pos - cameraOffset;

    hitbox = std::make_unique<Circle>(
        vec2(screenPos.x + image.width / 2.0f, screenPos.y + image.height / 2.0f),
        image.height / 4
    );

    for (unsigned int i = 0; i < image.width; i++) {
        for (unsigned int j = 0; j < image.height; j++) {
            if (image.alphaAt(i, j) > 200) {
                window.draw(screenPos.x + i, screenPos.y + j, image.at(i, j));

            }
        }
    }

    // Draw the hitbox for debugging purposes
    if (hitbox) {
        hitbox->draw(window);
    }
}
