#pragma once
#include <memory>
#include "core.h"
#include "vec2.h"
#include "GamesEngineeringBase.h"
#include "circle.h"

using namespace GamesEngineeringBase;

class Characters {
public:
    Characters(const std::string& sImage, vec2 startPos);
    virtual ~Characters() = default;
    void draw(Window& window, const vec2& cameraOffset);
    virtual void onUpdate() {}
    virtual void onUpdate(vec2 target) {}
    Shape* getHitbox() const { return hitbox.get(); }
    vec2 pos;
protected:
    Image image;
    std::unique_ptr<Shape> hitbox;
};
