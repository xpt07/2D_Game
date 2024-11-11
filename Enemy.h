#pragma once
#include "GameObject.h"
#include "Projectile.h"

/// @file Enemy.h
/// @brief Defines different types of enemies that inherit from the base GameObject class.

/// @class Enemy
/// @brief Abstract base class for all enemy types in the game.
class Enemy : public GameObject {
public:
    /**
     * @brief Constructor to initialize an enemy with a specific image, position, type, health, and speed.
     * @param sImage Path to the image file.
     * @param startPos Starting position of the enemy.
     * @param type Type of the enemy (e.g., Kamikaze, Bomber).
     * @param h Health of the enemy.
     * @param speed Speed of the enemy.
     */
    Enemy(const std::string& sImage, vec2 startPos, ObjectType type, int h, float speed);

    /**
     * @brief Constructor to initialize an enemy with a specific image, position, type, and speed (default health).
     * @param sImage Path to the image file.
     * @param startPos Starting position of the enemy.
     * @param type Type of the enemy (e.g., Kamikaze, Bomber).
     * @param speed Speed of the enemy.
     */
    Enemy(const std::string& sImage, vec2 startPos, ObjectType type, float speed);

    /**
     * @brief Pure virtual method to update the enemy's behavior.
     * @param target Position of the target (e.g., player position).
     * @param deltaTime Time since the last update.
     */
    virtual void onUpdate(vec2 target, float deltaTime) = 0;

    /// @brief Virtual destructor for cleanup.
    virtual ~Enemy() = default;

protected:
    float speed; ///< Speed of the enemy.
};

/// @class KamikazeEnemy
/// @brief Represents an enemy that flies directly towards the player.
class KamikazeEnemy : public Enemy {
public:
    /**
     * @brief Constructor to initialize a KamikazeEnemy.
     * @param startPos Starting position of the enemy.
     */
    KamikazeEnemy(vec2 startPos);

    /**
     * @brief Updates the KamikazeEnemy's behavior, making it move towards the target.
     * @param target Position of the target (e.g., player position).
     * @param deltaTime Time since the last update.
     */
    void onUpdate(vec2 target, float deltaTime) override;
};

/// @class BomberEnemy
/// @brief Represents an enemy that stops at a distance and shoots at the player.
class BomberEnemy : public Enemy {
public:
    /**
     * @brief Constructor to initialize a BomberEnemy with health.
     * @param startPos Starting position of the enemy.
     * @param h Health of the BomberEnemy.
     */
    BomberEnemy(vec2 startPos, int h);

    /**
     * @brief Updates the BomberEnemy's behavior, making it stop and shoot at the player.
     * @param target Position of the target (e.g., player position).
     * @param deltaTime Time since the last update.
     */
    void onUpdate(vec2 target, float deltaTime) override;

    /**
     * @brief Shoots a projectile towards the player if the cooldown timer has expired.
     * @param playerPos Position of the player.
     * @param projectiles Array of projectiles to add new shots.
     * @param projectileCount Current count of projectiles in the array.
     */
    void shootAtPlayer(vec2 playerPos, Projectile* projectiles[], int& projectileCount);

private:
    float attackDistance = 300.f; ///< Distance at which the BomberEnemy stops.
    float cooldownTimer; ///< Timer to track cooldown between shots.
    const float cooldownDuration = 1.0f; ///< Duration of the cooldown between shots.
};

/// @class DestroyerEnemy
/// @brief Represents an enemy that explodes and shoots projectiles when close to the player.
class DestroyerEnemy : public Enemy {
public:
    /**
     * @brief Constructor to initialize a DestroyerEnemy.
     * @param startPos Starting position of the enemy.
     */
    DestroyerEnemy(vec2 startPos);

    /**
     * @brief Updates the DestroyerEnemy's behavior, moving it towards the player and exploding when close.
     * @param target Position of the target (e.g., player position).
     * @param deltaTime Time since the last update.
     */
    void onUpdate(vec2 target, float deltaTime) override;

    /**
     * @brief Makes the DestroyerEnemy explode and shoot projectiles at the player.
     * @param playerPos Position of the player.
     * @param projectiles Array of projectiles to add new shots.
     * @param projectileCount Current count of projectiles in the array.
     */
    void explodeAndShoot(vec2 playerPos, Projectile* projectiles[], int& projectileCount);

    float attackDistance = 200.f; ///< Distance at which the DestroyerEnemy explodes.
};

/// @class SniperEnemy
/// @brief Represents an enemy that shoots at the player from a long distance.
class SniperEnemy : public Enemy {
public:
    /**
     * @brief Constructor to initialize a SniperEnemy.
     * @param startPos Starting position of the enemy.
     */
    SniperEnemy(vec2 startPos);

    /**
     * @brief Updates the SniperEnemy's behavior, making it shoot at the player from a distance.
     * @param target Position of the target (e.g., player position).
     * @param deltaTime Time since the last update.
     */
    void onUpdate(vec2 target, float deltaTime) override;

    /**
     * @brief Shoots a projectile at the player if the cooldown timer has expired.
     * @param playerPos Position of the player.
     * @param projectiles Array of projectiles to add new shots.
     * @param projectileCount Current count of projectiles in the array.
     */
    void shootAtPlayer(vec2 playerPos, Projectile* projectiles[], int& projectileCount);

private:
    float attackDistance = 500.f; ///< Distance at which the SniperEnemy shoots.
    float cooldownTimer; ///< Timer to track cooldown between shots.
    const float cooldownDuration = 3.0f; ///< Duration of the cooldown between shots.
};
