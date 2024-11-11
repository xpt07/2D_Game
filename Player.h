#pragma once
#include "GameObject.h"
#include "Projectile.h"

/// @file Player.h
/// @brief Defines the Player class, inheriting from GameObject, with specific functionality for the player character.

/// @class Player
/// @brief Represents the player character, handling movement, shooting, power-ups, and interactions with enemies.
class Player : public GameObject {
public:
    /// @brief Constructs a new Player object with default attributes.
    Player();

    /**
     * @brief Updates the player based on input and game logic.
     * @param canvas The window to render to.
     * @param deltaTime The time elapsed since the last update.
     * @param background The background of the game.
     * @param camera The camera for view management.
     */
    void onUpdate(Window& canvas, float deltaTime, Background& background, Camera& camera) override;

    /**
     * @brief Shoots a projectile at the nearest enemy if cooldown allows.
     * @param enemies An array of pointers to enemy objects.
     * @param enemyCount The number of enemies in the array.
     * @param projectiles An array of pointers to projectile objects.
     * @param projectileCount The current number of projectiles.
     */
    void shootAtNearestEnemy(GameObject* enemies[], int enemyCount, Projectile* projectiles[], int& projectileCount);

    /**
     * @brief Uses an area-of-effect (AOE) attack to damage multiple nearby enemies if cooldown allows.
     * @param enemies An array of pointers to enemy objects.
     * @param enemyCount The number of enemies in the array.
     */
    void useAOEAttack(GameObject* enemies[], int enemyCount);

    /// @brief Collects a power-up, enhancing the player's abilities temporarily.
    void collectPowerUp();

    /// @brief Gets the current position of the player.
    /// @return The current position as a vec2.
    vec2 getPosition() const { return pos; }

    /**
     * @brief Reduces the player's health by a specified amount.
     * @param amount The damage amount to subtract from health.
     */
    void takeDamage(int amount);

    /// @brief Checks if the player is still alive.
    /// @return True if health is greater than zero, false otherwise.
    bool isAlive() const { return health > 0; }

    /// @brief Resets the player's movement vector to (0, 0).
    void resetMovement() { movement = vec2(0, 0); }

private:
    float cooldownTimer; ///< The timer tracking the cooldown period for shooting.
    const float cooldownDuration = 1.f; ///< The duration of the shooting cooldown in seconds.

    float aoeCooldownTimer; ///< The timer tracking the cooldown period for the AOE attack.
    const float aoeCooldownDuration = 10.f; ///< The duration of the AOE attack cooldown in seconds.

    float fireRateMultiplier; ///< The multiplier for the player's shooting speed, modified by power-ups.
    float powerUpDuration; ///< The duration for which a power-up effect lasts.

    vec2 movement; ///< The player's current movement vector.
};
