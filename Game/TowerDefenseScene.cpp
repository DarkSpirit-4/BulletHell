#include "TowerDefenseScene.h"
#include "MapRenderer.h"
#include "EnemySpawnerT.h"
#include "Engine.h"
#include "Modules/WindowModule.h"
#include "Modules/InputModule.h"
#include "Modules/AssetsModule.h"
#include "Components/SpriteRenderer.h"
#include "TurretT.h"
#include "BaseT.h"
#include "MapData.h"
#include <iostream>

TowerDefenseScene::TowerDefenseScene()
    : Scene("TowerDefense", false)
{
    m_isInitialized = false;
    m_isHoldingTurret = false;
    m_selectedType = TurretType::BASIC;
}

void TowerDefenseScene::Update(const float _delta_time)
{
    Scene::Update(_delta_time);

    if (!m_isInitialized) {
        InitScene();
    }

    if (m_isInitialized) {
        HandlePlacement();
    }
}

void TowerDefenseScene::InitScene()
{
    auto* engine = Engine::GetInstance();
    if (!engine || !engine->GetModuleManager()) return;

    auto* mm = engine->GetModuleManager();
    auto* windowMod = mm->GetModule<WindowModule>();
    auto* assets = mm->GetModule<AssetsModule>();

    if (!windowMod || !assets) return;

    std::cout << "[TD] Modules trouves, lancement de la configuration..." << std::endl;

    windowMod->SetSize(Maths::Vector2u(1000, 800));
    windowMod->SetTitle("Sky Iron Armada - Tower Defense");

    if (GameObject* mapObj = CreateGameObject("LevelGrid"))
        mapObj->CreateComponent<MapRenderer>();

    if (GameObject* spawnerObj = CreateGameObject("EnemySpawner"))
        spawnerObj->CreateComponent<EnemySpawnerT>();

    if (GameObject* baseObj = CreateGameObject("Base"))
        baseObj->CreateComponent<BaseT>();

    auto setupIcon = [&](const std::string& name, float x, const std::string& texFile) {
        if (GameObject* icon = CreateGameObject(name)) {
            icon->SetPosition(Maths::Vector2f(x, 700.0f));
            Texture* tex = assets->GetAsset<Texture>(texFile);
            if (!tex) tex = assets->LoadAsset<Texture>(texFile);
            if (tex) icon->CreateComponent<SpriteRenderer>(tex);
        }
        };

    setupIcon("TurretIconBasic", 100.0f, "towerDefense_tile250.png");
    setupIcon("TurretIconAA", 200.0f, "towerDefense_tile205.png");

    m_isInitialized = true;
    std::cout << "[TD] Scene générée avec succès !" << std::endl;
}

void TowerDefenseScene::HandlePlacement()
{
    auto* mm = Engine::GetInstance()->GetModuleManager();
    auto* input = mm->GetModule<InputModule>();
    auto* windowMod = mm->GetModule<WindowModule>();
    auto* assets = mm->GetModule<AssetsModule>();

    if (!input || !windowMod || !assets) return;

    sf::RenderWindow* window = windowMod->GetWindow();
    if (!window) return;

    // Annulation (Clic droit)
    if (m_isHoldingTurret && input->GetMouseButtonDown(sf::Mouse::Button::Right)) {
        m_isHoldingTurret = false;
        std::cout << "[UI] Selection annulee." << std::endl;
        return;
    }

    if (input->GetMouseButtonDown(sf::Mouse::Button::Left))
    {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
        sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);

        if (worldPos.x >= 68.0f && worldPos.x <= 132.0f && worldPos.y >= 668.0f && worldPos.y <= 732.0f) {
            m_selectedType = TurretType::BASIC;
            m_isHoldingTurret = true;
            std::cout << "--- SELECTION FORCEE : BASIQUE ---" << std::endl;
            return;
        }
        else if (worldPos.x >= 168.0f && worldPos.x <= 232.0f && worldPos.y >= 668.0f && worldPos.y <= 732.0f) {
            m_selectedType = TurretType::ANTI_TANK;
            m_isHoldingTurret = true;
            std::cout << "--- SELECTION FORCEE : ANTI-AIR ---" << std::endl;
            return;
        }

        // --- PLACEMENT SUR LA GRILLE ---

        if (m_isHoldingTurret)
        {
            int gx = static_cast<int>(std::floor(worldPos.x / 64.0f));
            int gy = static_cast<int>(std::floor(worldPos.y / 64.0f));

            if (gx >= 0 && gx < MapData::WIDTH && gy >= 0 && gy < MapData::HEIGHT)
            {
                if (MapData::level1[gy][gx] == 0) // Si la case est libre
                {
                    GameObject* turret = CreateGameObject("Turret_" + std::to_string(gx) + "_" + std::to_string(gy));
                    turret->SetPosition(Maths::Vector2f(gx * 64.0f + 32.0f, gy * 64.0f + 32.0f));
                    turret->SetScale(Maths::Vector2f(0.5f, 0.5f));

                    TurretT* tComp = turret->CreateComponent<TurretT>();

                    tComp->SetType(m_selectedType);

                    std::string texName = (m_selectedType == TurretType::BASIC) ? "towerDefense_tile250.png" : "towerDefense_tile205.png";
                    Texture* tex = assets->GetAsset<Texture>(texName);
                    if (!tex) tex = assets->LoadAsset<Texture>(texName);

                    if (tex) {
                        turret->CreateComponent<SpriteRenderer>(tex);
                    }

                    std::cout << "[Placement] Succès ! Tourelle type " << (int)m_selectedType << " placée en " << gx << ":" << gy << std::endl;

                    MapData::level1[gy][gx] = 3;
                    m_isHoldingTurret = false;
                }
            }
        }
    }
}