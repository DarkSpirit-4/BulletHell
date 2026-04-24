#ifndef TOWERDEFENSESCENE_H
#define TOWERDEFENSESCENE_H

#include "Core/Scene.h"
#include "TurretT.h"

class TowerDefenseScene : public Scene
{
public:
    // Constructeur
    TowerDefenseScene();

    virtual ~TowerDefenseScene() = default;

    // Cycle de vie
    void Update(const float _delta_time) override;

    void InitScene();

private:

    void HandlePlacement();

    bool m_isInitialized = false;
    bool m_isHoldingTurret = false;

    TurretType m_selectedType = TurretType::BASIC;
};

#endif