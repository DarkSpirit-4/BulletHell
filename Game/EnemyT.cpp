#include "EnemyT.h"
#include "BaseT.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "MapData.h"
#include <iostream>
#include <cmath>
#include <string>

void EnemyT::Awake()
{
    m_targetPos = GetOwner()->GetPosition();
    m_lastGridPos = Maths::Vector2f(-1, -1);

    // Recherche immédiate du premier chemin
    FindNextWaypoint();
}

void EnemyT::SetStats(float _speed, int _hp, EnemyType _type)
{
    m_speed = _speed;
    m_hp = _hp;
    m_type = _type;

    std::string typeStr;
    switch (m_type)
    {
    case EnemyType::SCOUT: typeStr = "Scout"; break;
    case EnemyType::TANK:  typeStr = "Tank"; break;
    case EnemyType::BOSS:  typeStr = "Boss"; break;
    case EnemyType::PLANE: typeStr = "Avion (PLANE)"; break;
    default:               typeStr = "Inconnu"; break;
    }

    std::cout << "[Enemy] Apparition : " << typeStr << " | Vitesse: " << m_speed << " | HP: " << m_hp << std::endl;
}

void EnemyT::Update(const float _delta_time)
{
    Maths::Vector2f pos = GetOwner()->GetPosition();
    Maths::Vector2f direction = m_targetPos - pos;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    // Déplacement vers le point cible (waypoint)
    if (distance > 2.0f)
    {
        pos += (direction / distance) * m_speed * _delta_time;
        GetOwner()->SetPosition(pos);
    }
    else
    {
        // Point atteint, on cherche la suite du chemin
        FindNextWaypoint();
    }
}

void EnemyT::TakeDamage(int _amount)
{
    m_hp -= _amount;
    std::cout << "[Enemy] Degats recus: " << _amount << " | HP restants: " << m_hp << std::endl;

    if (m_hp <= 0)
    {
        std::cout << "[Enemy] Detruit au combat." << std::endl;

        auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
        if (sm)
        {
            Scene* currentScene = sm->GetSceneByName("TowerDefense");
            if (currentScene)
            {
                currentScene->DestroyGameObject(GetOwner());
            }
        }
    }
}

void EnemyT::FindNextWaypoint()
{
    Maths::Vector2f currentPos = GetOwner()->GetPosition();

    // Conversion en index de grille (basée sur la taille des tuiles définie dans MapData)
    int gx = static_cast<int>(currentPos.x / MapData::TILE_SIZE);
    int gy = static_cast<int>(currentPos.y / MapData::TILE_SIZE);

    float offset = MapData::TILE_SIZE * 0.5f;
    Maths::Vector2f currentGrid(static_cast<float>(gx), static_cast<float>(gy));

    // --- LOGIQUE DE NAVIGATION ---
    // On cherche une case de chemin (>= 1) qui n'est pas celle d'où l'on vient
    bool found = false;

    // 1. DROITE
    if (!found && gx + 1 < MapData::WIDTH && MapData::level1[gy][gx + 1] >= 1 && Maths::Vector2f(gx + 1, gy) != m_lastGridPos)
    {
        m_targetPos = Maths::Vector2f((gx + 1) * MapData::TILE_SIZE + offset, gy * MapData::TILE_SIZE + offset);
        found = true;
    }
    // 2. BAS
    else if (!found && gy + 1 < MapData::HEIGHT && MapData::level1[gy + 1][gx] >= 1 && Maths::Vector2f(gx, gy + 1) != m_lastGridPos)
    {
        m_targetPos = Maths::Vector2f(gx * MapData::TILE_SIZE + offset, (gy + 1) * MapData::TILE_SIZE + offset);
        found = true;
    }
    // 3. HAUT
    else if (!found && gy - 1 >= 0 && MapData::level1[gy - 1][gx] >= 1 && Maths::Vector2f(gx, gy - 1) != m_lastGridPos)
    {
        m_targetPos = Maths::Vector2f(gx * MapData::TILE_SIZE + offset, (gy - 1) * MapData::TILE_SIZE + offset);
        found = true;
    }
    // 4. GAUCHE
    else if (!found && gx - 1 >= 0 && MapData::level1[gy][gx - 1] >= 1 && Maths::Vector2f(gx - 1, gy) != m_lastGridPos)
    {
        m_targetPos = Maths::Vector2f((gx - 1) * MapData::TILE_SIZE + offset, gy * MapData::TILE_SIZE + offset);
        found = true;
    }

    m_lastGridPos = currentGrid;

    // --- ARRIVÉE À LA BASE (ID 2 sur la Map) ---
    if (MapData::level1[gy][gx] == 2)
    {
        auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
        if (sm)
        {
            Scene* currentScene = sm->GetSceneByName("TowerDefense");
            if (currentScene)
            {
                const auto& objects = currentScene->GetGameObjects();
                for (const auto& objPtr : objects)
                {
                    // On cherche l'objet nommé "Base" pour lui infliger des dégâts
                    if (objPtr->GetName() == "Base")
                    {
                        if (BaseT* base = objPtr->GetComponent<BaseT>())
                            base->TakeDamage(1);
                        break;
                    }
                }
                currentScene->DestroyGameObject(GetOwner());
            }
        }
    }
}