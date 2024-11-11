#pragma once
#include "GameObject.h"

/// @file PowerUp.h
/// @brief Defines the PowerUp class, a collectible item that grants the player temporary abilities.

/// @class PowerUp
/// @brief Represents a collectible power-up in the game that enhances the player's abilities when collected.
class PowerUp : public GameObject {
public:
    /**
     * @brief Constructs a PowerUp object at the specified position.
     * @param startPos The starting position of the power-up.
     */
    PowerUp(vec2 startPos);

    /**
     * @brief Draws the power-up on the window, taking into account the camera's position.
     * @param window The window to draw to.
     * @param cameraOffset The camera offset to apply when drawing.
     */
    void draw(Window& window, const vec2& cameraOffset);

    /**
     * @brief Checks if the power-up has been collected.
     * @return True if the power-up is collected, false otherwise.
     */
    bool isCollected() const { return collected; }

private:
    bool collected; ///< A flag indicating whether the power-up has been collected by the player.
};
