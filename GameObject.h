#pragma once
#include <memory>
#include "Background.h"
#include "core.h"

using namespace GamesEngineeringBase;

enum class ObjectType {
    Player,
    Kamikaze,
    Bomber,
    Projectile,
    PowerUp
};

class GameObject {
public:
    GameObject(const std::string& sImage, vec2 startPos, ObjectType type, int h = 100);
    GameObject(vec2 startPos, ObjectType type) : pos(startPos), charType(type) {};
    virtual ~GameObject() = default;
    virtual void onUpdate(Window& canvas, float deltaTime, Background& background, Camera& camera) {}
    virtual void onUpdate(vec2 target, float deltaTime) {}
    virtual void onUpdate() {}
    void takeDamage(int amount);
    void draw(Window& window, const vec2& cameraOffset);
    Shape* getHitbox() const { return hitbox.get(); }
    vec2 getPosition() const { return pos; }
    ObjectType getCharacterType() { return charType; }
    int getHealth() const { return health; }
protected:
    vec2 pos;
    Image image;
    int health;
    std::unique_ptr<Shape> hitbox;
    ObjectType charType;
};
