#pragma once
#include "Characters.h"
#include "Rect.h"

class Player : public Characters {
public:
    Player() : Characters("resources/mainShip.png", vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT /2)) {}
    vec2 getPosition() const { return pos; }
    void onUpdate() override
    {
        // Update the position of the hitbox to stay aligned with the enemy
        if (Circle* circ = dynamic_cast<Circle*>(hitbox.get())) {
            circ->setCenter(vec2(pos.x + image.width / 2.0f, pos.y + image.height / 2.0f));
        }
    }
};
