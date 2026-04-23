#pragma once

#include "Core/Component.h"

class AsteroidSpawner : public Component
{
public:
    float spawnRate = 0.15f;
    bool canSpawnLaser = false;
    float timer = 0.f;

    void Update(float dt) override;
private:
    float asteroidTimer = 0.0f;
    float laserTimer = 0.0f;
    float laserInterval = 4.0f;
};