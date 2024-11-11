#pragma once

#include <iostream>
#include <cmath>

/// @file vec2.h
/// @brief Defines a 2D vector class for mathematical operations.

/// @class vec2
/// @brief Represents a 2D vector with x and y components and provides various operations.
class vec2 {
public:
    float x, y; ///< The x and y components of the vector.

    /// @brief Default constructor that initializes the vector to (0, 0).
    vec2() : x(0), y(0) {}

    /// @brief Constructor that initializes the vector with specified x and y components.
    /// @param _x The x component of the vector.
    /// @param _y The y component of the vector.
    vec2(float _x, float _y) : x(_x), y(_y) {}

    /// @brief Sets the position of the vector.
    /// @param _x The new x component.
    /// @param _y The new y component.
    void setPos(float _x, float _y) {
        x = _x;
        y = _y;
    }

    /// @brief Gets the current position of the vector.
    /// @return A new vec2 object representing the current position.
    vec2 getPos() { return vec2(x, y); }

    /// @brief Calculates the length (magnitude) of the vector.
    /// @return The length of the vector.
    float getLength() {
        return std::sqrt(x * x + y * y); // Corrected the length calculation formula.
    }

    /// @brief Adds two vectors and returns the result.
    /// @param v The vector to add.
    /// @return A new vec2 object that is the sum of the two vectors.
    vec2 operator+(const vec2& v) const {
        return vec2(x + v.x, y + v.y);
    }

    /// @brief Subtracts a vector from the current vector and returns the result.
    /// @param v The vector to subtract.
    /// @return A new vec2 object that is the difference of the two vectors.
    vec2 operator-(const vec2& v) const {
        return vec2(x - v.x, y - v.y);
    }

    /// @brief Subtracts a scalar from both components of the vector and returns the result.
    /// @param v The scalar value to subtract.
    /// @return A new vec2 object with the result.
    vec2 operator-(const float& v) const {
        return vec2(x - v, y - v);
    }

    /// @brief Adds a scalar to both components of the vector and returns the result.
    /// @param v The scalar value to add.
    /// @return A new vec2 object with the result.
    vec2 operator+(const float& v) const {
        return vec2(x + v, y + v);
    }

    /// @brief Divides both components of the vector by a scalar and returns the result.
    /// @param value The scalar value to divide by.
    /// @return A new vec2 object with the result, or the original vector if value is zero.
    vec2 operator/(const float value) const {
        if (value != 0) {
            return vec2(x / value, y / value);
        }
        else {
            std::cerr << "Attempt to divide by zero." << std::endl;
            return *this; // Return the original vector if divide by zero
        }
    }

    /// @brief Divides both components of the vector by a scalar and updates the vector.
    /// @param value The scalar value to divide by.
    void operator/=(const float value) {
        if (value != 0) {
            x /= value;
            y /= value;
        }
        else {
            std::cerr << "Attempt to divide by zero." << std::endl;
        }
    }

    /// @brief Multiplies both components of the vector by a scalar and returns the result.
    /// @param value The scalar value to multiply by.
    /// @return A new vec2 object with the result.
    vec2 operator*(const float value) const {
        return vec2(x * value, y * value);
    }

    /// @brief Adds another vector to the current vector and updates it.
    /// @param v The vector to add.
    void operator+=(const vec2& v) {
        x += v.x;
        y += v.y;
    }

    /// @brief Subtracts another vector from the current vector and updates it.
    /// @param v The vector to subtract.
    void operator-=(const vec2& v) {
        x -= v.x;
        y -= v.y;
    }

private:
    // No private members or methods are defined.
};
