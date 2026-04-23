#pragma once

#include "Core/Component.h"

enum class GamePhase
{
    Asteroids1,
    BulletHell1,
    Asteroids2,
    BulletHell2
};

class GameManager : public Component
{
public:
    bool canSpawnLaser = false;
    void Update(float dt) override;

private:
    float timer = 0.f;
    GamePhase currentPhase = GamePhase::Asteroids1;

    void SwitchPhase(GamePhase newPhase);
};