#pragma once
#include "GameObject.h"
#include "Projectile.h"
#include <vector>

class Enemy : public GameObject {
public:
    Enemy(const std::string& sImage, vec2 startPos, ObjectType type, float speed);
    void onUpdate(vec2 target, float deltaTime) override = 0;
    virtual ~Enemy() = default;

protected:
    float speed;  // Distance at which the Bomber stops approaching
};

class KamikazeEnemy : public Enemy {
public:
    KamikazeEnemy(vec2 startPos);
    void onUpdate(vec2 target, float deltaTime) override;
};

class BomberEnemy : public Enemy {
public:
    BomberEnemy(vec2 startPos);
    void onUpdate(vec2 target, float deltTime) override;
    void shootAtPlayer(vec2 playerPos, std::vector<std::unique_ptr<Projectile>>& projectiles);

private: 
    float attackDistance = 300.f;
    float cooldownTimer;       // Timer to track cooldown
    const float cooldownDuration = 1.0f;  // Cooldown duration in seconds
};