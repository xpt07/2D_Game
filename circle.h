#pragma once

#include "Shape.h"
#include <cmath>

/// @file circle.h
/// @brief Defines the Circle class, which represents a circle shape.

/// @class Circle
/// @brief Represents a circle and provides methods to check if a point is inside, calculate the area, and draw the circle.
class Circle : public Shape {
public:
    /// @brief Constructor that initializes the circle with a center and a radius.
    /// @param c The center of the circle.
    /// @param r The radius of the circle.
    Circle(vec2 c, float r) : centre(c), radius(r) {}

    /// @brief Checks if a given point is inside the circle.
    /// @param p The point to check.
    /// @return True if the point is inside the circle, false otherwise.
    bool inside(vec2 p) override {
        float distanceSquared = (p.x - centre.x) * (p.x - centre.x) + (p.y - centre.y) * (p.y - centre.y);
        return distanceSquared <= radius * radius;
    }

    /// @brief Calculates the area of the circle.
    /// @return The area of the circle.
    float area() override {
        return 3.14159f * radius * radius;
    }

    /// @brief Draws the circle on the given window.
    /// @param window The window on which to draw the circle.
    void draw(Window& window) override {
        for (int x = static_cast<int>(centre.x - radius); x <= static_cast<int>(centre.x + radius); x++) {
            for (int y = static_cast<int>(centre.y - radius); y <= static_cast<int>(centre.y + radius); y++) {
                // Check if the point (x, y) is inside the circle
                if (inside(vec2(x, y))) {
                    window.draw(x, y, 255, 255, 255); // Draw in white color
                }
            }
        }
    }

    /// @brief Sets the center of the circle to a new position.
    /// @param newCentre The new center position.
    void setCentre(vec2 newCentre) {
        centre = newCentre;
    }

    /// @brief Gets the center of the circle.
    /// @return The current center of the circle.
    vec2 getCenter() { return centre; }

    /// @brief Gets the radius of the circle.
    /// @return The radius of the circle.
    float getRadius() { return radius; }

private:
    vec2 centre; ///< The center of the circle.
    float radius; ///< The radius of the circle.
};
