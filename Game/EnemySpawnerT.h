#pragma once

#include "Core/Component.h"

class EnemySpawnerT : public Component {
public:
    void Update(const float _delta_time) override;
private:
    void Spawn();

    float m_timer = 0.0f;
    float m_interval = 2.5f;
    int m_spawnedCount = 0;
    int m_maxEnemies = 50;
};