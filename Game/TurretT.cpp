#include "TurretT.h"
#include "EnemyT.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Maths/Vector2.h"
#include <cmath>
#include <iostream>

void TurretT::Awake()
{
    m_damageTimer = 0.0f;

}

void TurretT::SetType(TurretType _type)
{
    m_type = _type;

    if (m_type == TurretType::ANTI_TANK)
    {
        m_range = 350.0f;
        m_fireRate = 0.5f;
        m_damage = 1;
        std::cout << "[DEBUG internal] Tourelle configuree en ANTI-AIR" << std::endl;
    }
    else
    {
        m_range = 200.0f;
        m_fireRate = 1.0f;
        m_damage = 1;
        std::cout << "[DEBUG internal] Tourelle configuree en BASIC" << std::endl;
    }
}

void TurretT::Update(const float _delta_time)
{
    m_damageTimer += _delta_time;

    if (m_damageTimer < m_fireRate) return;

    auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    if (!sm) return;

    Scene* currentScene = sm->GetSceneByName("TowerDefense");
    if (!currentScene) return;

    const auto& objects = currentScene->GetGameObjects();
    Maths::Vector2f myPos = GetOwner()->GetPosition();

    for (const auto& objPtr : objects)
    {
        GameObject* obj = objPtr.get();
        if (!obj) continue;

        EnemyT* enemy = obj->GetComponent<EnemyT>();
        if (enemy)
        {

            int turretT = (int)m_type;
            int enemyT = (int)enemy->GetType();

            if (m_type == TurretType::ANTI_TANK)
            {
                // Si la tourelle est AA (1) et l'ennemi n'est pas PLANE (3), on passe au suivant
                if (enemy->GetType() != EnemyType::PLANE) continue;
            }
            else
            {
                // Si la tourelle est BASIC (0) et l'ennemi est PLANE (3), on ignore
                if (enemy->GetType() == EnemyType::PLANE) continue;
            }

            // --- CALCUL ET TIR ---
            Maths::Vector2f enemyPos = obj->GetPosition();
            Maths::Vector2f diff = enemyPos - myPos;
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);

            if (dist <= m_range)
            {
                enemy->TakeDamage(m_damage);
                m_damageTimer = 0.0f;

                // Debug console
                if (m_type == TurretType::ANTI_TANK)
                {
                    std::cout << "[DCA-AA] Tir validé (Type:" << turretT << ") sur Cible (Type:" << enemyT << ")" << std::endl;
                }
                else
                {
                    std::cout << "[Mitrailleuse] Tir validé (Type:" << turretT << ") sur Cible (Type:" << enemyT << ")" << std::endl;
                }

                return;
            }
        }
    }
}