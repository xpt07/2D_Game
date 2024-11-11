#pragma once

#include "core.h"

using namespace GamesEngineeringBase;

/// @file Shape.h
/// @brief Defines the abstract base class for different geometric shapes.

/// @class Shape
/// @brief Abstract base class that represents a generic shape.
class Shape {
public:
    /// @brief Checks if a given point is inside the shape.
    /// @param p The point to check.
    /// @return True if the point is inside the shape, false otherwise.
    virtual bool inside(vec2 p) = 0;

    /// @brief Calculates the area of the shape.
    /// @return The area of the shape.
    virtual float area() = 0;

    /// @brief Draws the shape on the given window.
    /// @param window The window on which to draw the shape.
    virtual void draw(Window& window) = 0;

private:
    float radius; ///< The radius of the shape.
};
