#pragma once
#include "vec2.h"
#include "GamesEngineeringBase.h"

using namespace GamesEngineeringBase;

class Characters {
public:
    Characters(const std::string& sImage, vec2 startPos);
    virtual ~Characters() = default;
    virtual void draw(Window& window, const vec2& position);

protected:
    Image image;
    vec2 pos;
};
