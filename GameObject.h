#pragma once
#include <memory>
#include "Background.h"
#include "core.h"

using namespace GamesEngineeringBase;

/// @file GameObject.h
/// @brief Defines the base class for all game objects and provides common functionality.

/// @enum ObjectType
/// @brief Enum class that specifies different types of game objects.
enum class ObjectType {
    Player,     ///< The player's character.
    Kamikaze,   ///< A Kamikaze enemy type.
    Bomber,     ///< A Bomber enemy type.
    Destroyer,  ///< A Destroyer enemy type.
    Sniper,     ///< A Sniper enemy type.
    Projectile, ///< A projectile, such as a bullet or missile.
    PowerUp     ///< A power-up item that can be collected by the player.
};

/// @class GameObject
/// @brief The base class for all game objects, providing common properties and methods.
class GameObject {
public:
    /**
     * @brief Constructs a GameObject with an image, starting position, type, and health.
     * @param sImage The path to the image file.
     * @param startPos The initial position of the object.
     * @param type The type of the object (e.g., Player, Bomber).
     * @param h The health of the object. Defaults to 100.
     */
    GameObject(const std::string& sImage, vec2 startPos, ObjectType type, int h = 100);

    /**
     * @brief Constructs a GameObject with a starting position and type (no image or default health).
     * @param startPos The initial position of the object.
     * @param type The type of the object.
     */
    GameObject(vec2 startPos, ObjectType type) : pos(startPos), charType(type) {};

    /// @brief Virtual destructor for cleanup.
    virtual ~GameObject() = default;

    /**
     * @brief Updates the object. Overloaded for specific behavior in derived classes.
     * @param canvas The window to render to.
     * @param deltaTime The time elapsed since the last update.
     * @param background The background of the game.
     * @param camera The camera for view management.
     */
    virtual void onUpdate(Window& canvas, float deltaTime, Background& background, Camera& camera) {}

    /**
     * @brief Updates the object using a target position and elapsed time. Used for enemies.
     * @param target The position to target.
     * @param deltaTime The time elapsed since the last update.
     */
    virtual void onUpdate(vec2 target, float deltaTime) {}

    /// @brief A simple update method without parameters, for general updates.
    virtual void onUpdate() {}

    /**
     * @brief Reduces the object's health by a specified amount.
     * @param amount The damage amount to subtract from health.
     */
    void takeDamage(int amount);

    /**
     * @brief Draws the object on the window, adjusted by the camera offset.
     * @param window The window to draw on.
     * @param cameraOffset The offset to apply based on the camera position.
     */
    void draw(Window& window, const vec2& cameraOffset);

    /// @brief Gets the hitbox shape of the object.
    /// @return A pointer to the hitbox shape.
    Shape* getHitbox() const { return hitbox.get(); }

    /// @brief Gets the current position of the object.
    /// @return The current position as a vec2.
    vec2 getPosition() const { return pos; }

    /// @brief Sets the position of the object.
    /// @param _pos The new position to set.
    void setPosition(vec2 _pos) { pos = _pos; }

    /// @brief Gets the type of the object.
    /// @return The object type.
    ObjectType getCharacterType() { return charType; }

    /// @brief Gets the health of the object.
    /// @return The current health.
    int getHealth() const { return health; }

    /// @brief Sets the health of the object.
    /// @param _health The new health value.
    void setHealth(int _health) { health = _health; }

protected:
    vec2 pos; ///< The position of the object in the game world.
    Image image; ///< The image representing the object.
    int health; ///< The health of the object (in this case only for the Player and Enemy classes).
    std::unique_ptr<Shape> hitbox; ///< The hitbox used for collision detection.
    ObjectType charType; ///< The type of the object (e.g., Player, Bomber, etc.).
};
