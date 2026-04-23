#include "LaserTrap.h"
#include "Core/GameObject.h"
#include "Components/RectangleShapeRenderer.h"
#include "SquareCollider.h"
#include "Health.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Core/Scene.h"
#include <cmath>
#include <iostream>

void LaserTrap::Update(float _deltaTime)
{
    GameObject* owner = GetOwner();
    if (!owner) return;

    timer += _deltaTime;

    auto* renderer = owner->GetComponent<RectangleShapeRenderer>();
    if (!renderer) return;

    // --- PHASE ALERTE (CLIGNOTEMENT) ---
    if (!isDangerouslyActive && timer < warningDuration)
    {
        float sinVal = (std::sin(timer * 20.0f) * 0.5f) + 0.5f;
        int alpha = static_cast<int>(sinVal * 100.0f) + 20;
        renderer->SetColor(sf::Color(255, 0, 0, (unsigned char)alpha));
    }
    // --- PHASE DANGER (LASER PLEIN) ---
    else if (!isDangerouslyActive && timer >= warningDuration)
    {
        isDangerouslyActive = true;
        renderer->SetColor(sf::Color::Red);
    }

    // Dans LaserTrap.cpp - Section détection de collision
    if (isDangerouslyActive)
    {
        auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
        Scene* scene = sm->GetScenesList().front().get();

        GameObject* player = nullptr;
        for (const auto& obj : scene->GetGameObjects()) {
            if (obj->GetName() == "Player") {
                player = obj.get();
                break;
            }
        }

        if (player) {
            auto* pCol = player->GetComponent<SquareCollider>();
            if (pCol) {
                // Rect du Laser
                Maths::Vector2f lPos = owner->GetPosition();
                Maths::Vector2f lSize = renderer->GetSize();

                // Rect du Joueur
                Maths::Vector2f pPos = player->GetPosition();
                float pW = pCol->GetWidth();
                float pH = pCol->GetHeight();

                // TEST AABB
                bool overlapX = lPos.x < pPos.x + pW && lPos.x + lSize.x > pPos.x;
                bool overlapY = lPos.y < pPos.y + pH && lPos.y + lSize.y > pPos.y;

                if (overlapX && overlapY) {
                    auto* hp = player->GetComponent<Health>();
                    if (hp) {
                        // Appeler la fonction officielle plutôt que de toucher à la variable
                        hp->TakeDamage(1);

                        // Debug pour voir si TakeDamage est bien appelé
                        // std::cout << "Appel de TakeDamage via le laser !" << std::endl;
                    }
                
                }
            }
        }
    }

    // --- DESTRUCTION ---
    if (timer >= (warningDuration + activeDuration))
    {
        owner->Destroy();
    }
}