#pragma once
#include <memory>
#include "core.h"
#include "vec2.h"
#include "GamesEngineeringBase.h"
#include "circle.h"

using namespace GamesEngineeringBase;

enum class ObjectType {
    Player,
    Kamikaze,
    Bomber,
    Projectile
};

class GameObject {
public:
    GameObject(const std::string& sImage, vec2 startPos, ObjectType type, int h = 100);
    GameObject(vec2 startPos, ObjectType type) : pos(startPos), charType(type) {};
    virtual ~GameObject() = default;
    virtual void onUpdate(Window& canvas, float deltaTime) {}
    virtual void onUpdate(vec2 target, float deltaTime) {}
    virtual void onUpdate() {}
    void draw(Window& window, const vec2& cameraOffset);
    Shape* getHitbox() const { return hitbox.get(); }
    vec2 getPosition() const { return pos; }
    ObjectType getCharacterType() const { return charType; }
protected:
    vec2 pos;
    Image image;
    int health;
    std::unique_ptr<Shape> hitbox;
    ObjectType charType;
};
