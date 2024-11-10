#pragma once
#include "core.h"

class Camera {
public:
    Camera(int windowWidth, int windowHeight)
        : windowWidth(windowWidth), windowHeight(windowHeight) {}

    void follow(const vec2& target) {
        // Center the camera on the target
        position = target - vec2(windowWidth / 2, windowHeight / 2);
    }

    vec2 getPosition() const { return position; }

private:
    vec2 position;
    int windowWidth, windowHeight;
};
