#pragma once
#include "core.h"

/// Class representing the camera used for tracking and centering the player's view in the game world
class Camera {
public:
    /**
     * @brief Constructs a Camera object
     *
     * @param windowWidth The width of the game window
     * @param windowHeight The height of the game window
     */
    Camera(int windowWidth, int windowHeight)
        : windowWidth(windowWidth), windowHeight(windowHeight) {}

    /**
     * @brief Centers the camera on a specified target position
     *
     * @param target The target position to center the camera on
     */
    void follow(const vec2& target) {
        // Center the camera on the target
        position = target - vec2(windowWidth / 2, windowHeight / 2);
    }

    /**
     * @brief Gets the current position of the camera
     *
     * @return The current position of the camera as a vec2
     */
    vec2 getPosition() const { return position; }

private:
    vec2 position;           ///< The current position of the camera
    int windowWidth;         ///< The width of the game window
    int windowHeight;        ///< The height of the game window
};
