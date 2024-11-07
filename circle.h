#pragma once
#include "Shape.h"
#include <cmath>

class Circle : public Shape {
public:
    Circle(vec2 c, float r) : centre(c), radius(r) {}

    // Check if a point is inside the circle
    bool inside(vec2 p) override {
        float distanceSquared = (p.x - centre.x) * (p.x - centre.x) + (p.y - centre.y) * (p.y - centre.y);
        return distanceSquared <= radius * radius;
    }

    // Calculate the area of the circle
    float area() override {
        return 3.14159f * radius * radius;
    }

    // Draw the circle on the window
    void draw(Window& window) override {
        for (int x = static_cast<int>(centre.x - radius); x <= static_cast<int>(centre.x + radius); x++) {
            for (int y = static_cast<int>(centre.y - radius); y <= static_cast<int>(centre.y + radius); y++) {
                // Check if the point (x, y) is inside the circle
                if (inside(vec2(x, y))) {
                    window.draw(x, y, 255, 255, 255); // White color
                }
            }
        }
    }

    void setCenter(vec2 newCentre) {
        centre = newCentre;
    }

private:
    vec2 centre;
    float radius;
};
