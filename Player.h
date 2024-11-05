#pragma once
#include "Characters.h"

class Player : public Characters {
public:
    Player();
    void draw(Window& window);
};
