#pragma once

#include "Core/Component.h"

class BulletManager : public Component
{
public:
    void Update(float _delta_time) override;

private:
    float spawnTimer = 0.0f;
    float spawnRate = 0.25f; // Pluie plus rapide pour bien voir l'effet
    float angle = 0.0f;     // L'angle actuel du spawn
};