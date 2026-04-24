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
    std::cout << "Laser Timer: " << timer << " / Target: " << (warningDuration + activeDuration) << std::endl;
    GameObject* owner = GetOwner();
    if (!owner) return;

    timer += _deltaTime;

    auto* renderer = owner->GetComponent<RectangleShapeRenderer>();
    if (!renderer) return;

    // --- 1. GESTION DES ÉTATS VISUELS ---
    // Tant qu'on est sous la durée d'alerte, on fait clignoter
    if (timer < warningDuration)
    {
        float sinVal = (std::sin(timer * 20.0f) * 0.5f) + 0.5f;
        int alpha = static_cast<int>(sinVal * 100.0f) + 20;
        renderer->SetColor(sf::Color(255, 0, 0, (unsigned char)alpha));
    }
    // Une fois le temps d'alerte passé, on passe en rouge plein
    else if (timer < (warningDuration + activeDuration))
    {
        if (!isDangerouslyActive)
        {
            isDangerouslyActive = true;
            renderer->SetColor(sf::Color::Red);
        }
    }

    // --- 2. DÉTECTION DE COLLISION ---
    // Cette section ne s'exécute que si le laser est en phase "DANGER"
    if (isDangerouslyActive)
    {
        auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
        if (sm)
        {
            // On cible spécifiquement la scène de jeu
            Scene* scene = sm->GetSceneByName("BulletHell");
            if (scene)
            {
                GameObject* player = nullptr;
                for (const auto& obj : scene->GetGameObjects())
                {
                    if (obj->GetName() == "Player") {
                        player = obj.get();
                        break;
                    }
                }

                if (player)
                {
                    auto* pCol = player->GetComponent<SquareCollider>();
                    if (pCol)
                    {
                        // Rect du Laser
                        Maths::Vector2f lPos = owner->GetPosition();
                        Maths::Vector2f lSize = renderer->GetSize();

                        // Rect du Joueur
                        Maths::Vector2f pPos = player->GetPosition();
                        float pW = pCol->GetWidth();
                        float pH = pCol->GetHeight();

                        // Test de collision AABB simple
                        bool overlapX = lPos.x < pPos.x + pW && lPos.x + lSize.x > pPos.x;
                        bool overlapY = lPos.y < pPos.y + pH && lPos.y + lSize.y > pPos.y;

                        if (overlapX && overlapY)
                        {
                            auto* hp = player->GetComponent<Health>();
                            if (hp) hp->TakeDamage(1);
                        }
                    }
                }
            }
        }
    }

    // --- 3. DESTRUCTION AUTOMATIQUE ---
    if (timer >= (warningDuration + activeDuration))
    {
        // 1. Récupérer le module de scène
        auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
        if (sm)
        {
            // 2. Récupérer la scène active (ici nommée "BulletHell")
            Scene* scene = sm->GetSceneByName("BulletHell");
            if (scene)
            {
                // On demande à la scène de supprimer cet objet spécifique
                scene->DestroyGameObject(owner);
                return; // On arrête l'Update ici
            }
        }

        // Si la méthode ci-dessus n'existe pas dans ton moteur, 
        // utilise simplement la méthode standard :
        owner->Destroy();
   
    }
}