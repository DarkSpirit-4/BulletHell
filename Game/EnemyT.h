#ifndef ENEMYT_H
#define ENEMYT_H

#include "Core/Component.h"
#include "Maths/Vector2.h"
#include <vector>

enum class EnemyType { SCOUT, TANK, BOSS, PLANE };

class EnemyT : public Component
{
public:

    void Awake() override;
    void Update(const float _delta_time) override;

    // Configuration
    void SetStats(float _speed, int _hp, EnemyType _type = EnemyType::SCOUT);
    void TakeDamage(int _amount);

    EnemyType GetType() const { return m_type; }
    int GetHp() const { return m_hp; }

private:
    void FindNextWaypoint();

    float m_speed = 100.0f;
    int m_hp = 10;
    EnemyType m_type = EnemyType::SCOUT;

    // Navigation
    Maths::Vector2f m_targetPos;
    Maths::Vector2f m_lastGridPos;
};

#endif