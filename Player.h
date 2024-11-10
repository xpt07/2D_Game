#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include <vector>

class Player : public GameObject {
public:
    Player();

    void onUpdate(Window& canvas, float deltaTime, Background& background, Camera& camera) override;
    void shootAtNearestEnemy(std::vector<std::unique_ptr<GameObject>>& enemies, std::vector<std::unique_ptr<Projectile>>& projectiles);

    vec2 getPosition() const { return pos; }
    void takeDamage(int amount);
    bool isAlive() const { return health > 0; }

private:
    float cooldownTimer;
    const float cooldownDuration = 1.0f;
};
