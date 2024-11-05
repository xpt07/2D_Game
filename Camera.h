#pragma once
#include "vec2.h"

class Camera {
public:
    Camera(int width, int height) : width(width), height(height), position(0, 0) {}

    void follow(const vec2& target, float lerpFactor = 0.5f) {
        position.x += (target.x - position.x) * lerpFactor;
        position.y += (target.y - position.y) * lerpFactor;
    }

    vec2 getPosition() const { return position; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    vec2 position;
    int width;
    int height;
};
