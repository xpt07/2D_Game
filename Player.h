#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include <vector>

class Player : public GameObject {
public:
    Player();

    void onUpdate(Window& canvas, float deltaTime, Background& background, Camera& camera) override;
    void shootAtNearestEnemy(std::vector<std::unique_ptr<GameObject>>& enemies, std::vector<std::unique_ptr<Projectile>>& projectiles);
    void useAOEAttack(std::vector<std::unique_ptr<GameObject>>& enemies);
    void collectPowerUp();
    vec2 getPosition() const { return pos; }
    void takeDamage(int amount);
    bool isAlive() const { return health > 0; }

private:
    float cooldownTimer;
    const float cooldownDuration = 1.f;

    float aoeCooldownTimer;
    const float aoeCooldownDuration = 10.f;

    float fireRateMultiplier;
    float powerUpDuration;
};
