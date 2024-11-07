#pragma once
#include "Characters.h"

enum class EnemyType { Kamikaze = 0, Bomber };

class Enemy : public Characters {
public:
    Enemy(const std::string& sImage, vec2 startPos, EnemyType type);
    void onUpdate() override;
    EnemyType getType() const { return type; }

private:
    EnemyType type;
    vec2 position;
};
