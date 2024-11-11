#pragma once
#include "GameObject.h"
#include "Projectile.h"

class Enemy : public GameObject {
public:
    Enemy(const std::string& sImage, vec2 startPos, ObjectType type, int h, float speed);
    Enemy(const std::string& sImage, vec2 startPos, ObjectType type, float speed);
    virtual void onUpdate(vec2 target, float deltaTime) = 0;
    virtual ~Enemy() = default;
protected:
    float speed;
};

class KamikazeEnemy : public Enemy {
public:
    KamikazeEnemy(vec2 startPos);
    void onUpdate(vec2 target, float deltaTime) override;
};

class BomberEnemy : public Enemy {
public:
    BomberEnemy(vec2 startPos, int h);
    void onUpdate(vec2 target, float deltaTime) override;
    void shootAtPlayer(vec2 playerPos, Projectile* projectiles[], int& projectileCount);
private:
    float attackDistance = 300.f;
    float cooldownTimer;
    const float cooldownDuration = 1.0f;
};

class DestroyerEnemy : public Enemy {
public:
    DestroyerEnemy(vec2 startPos);
    void onUpdate(vec2 target, float deltaTime) override;
    void explodeAndShoot(vec2 playerPos, Projectile* projectiles[], int& projectileCount);
    float attackDistance = 200.f;
};

class SniperEnemy : public Enemy {
public:
    SniperEnemy(vec2 startPos);
    void onUpdate(vec2 target, float deltaTime) override;
    void shootAtPlayer(vec2 playerPos, Projectile* projectiles[], int& projectileCount);
private:
    float attackDistance = 500.f;
    float cooldownTimer;
    const float cooldownDuration = 3.0f;
};
