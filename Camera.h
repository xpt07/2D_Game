#pragma once
#include "vec2.h"

class Camera
{
public:
    vec2 position;

    Camera() : position(0, 0) {}

    void move(float dx, float dy) {
        position.x += dx;
        position.y += dy;
    }

    // Get the offset X position
    int offsetX() const {
        return static_cast<int>(position.x);
    }

    // Get the offset Y position
    int offsetY() const {
        return static_cast<int>(position.y);
    }
};
