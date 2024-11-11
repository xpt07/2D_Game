#pragma once
#include "GameObject.h"
#include "Projectile.h"

class Player : public GameObject {
public:
    Player();

    void onUpdate(Window& canvas, float deltaTime, Background& background, Camera& camera) override;
    void shootAtNearestEnemy(GameObject* enemies[], int enemyCount, Projectile* projectiles[], int& projectileCount);
    void useAOEAttack(GameObject* enemies[], int enemyCount);
    void collectPowerUp();
    vec2 getPosition() const { return pos; }
    void takeDamage(int amount);
    bool isAlive() const { return health > 0; }
    void resetMovement() { movement = vec2(0, 0); }
private:
    float cooldownTimer;
    const float cooldownDuration = 1.f;

    float aoeCooldownTimer;
    const float aoeCooldownDuration = 10.f;

    float fireRateMultiplier;
    float powerUpDuration;

    vec2 movement;
};
