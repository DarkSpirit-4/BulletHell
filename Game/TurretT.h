#ifndef TURRETT_H
#define TURRETT_H

#include "Core/Component.h"
#include <string>
#include <memory>

enum class TurretType {
    BASIC,
    ANTI_TANK
};

class TurretT : public Component
{
public:
    TurretT() = default;

    void Awake() override;
    void Update(const float _delta_time) override;

    // Configurer la tourelle lors du placement
    void SetType(TurretType _type);

    TurretType GetType() const { return m_type; }

private:
    TurretType m_type = TurretType::BASIC;

    float m_range = 200.0f;
    float m_fireRate = 1.0f;
    float m_damageTimer = 0.0f;
    int m_damage = 1;
};

#endif