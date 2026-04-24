#include "Health.h"
#include "Core/GameObject.h"
#include "Engine.h"
#include "Components/SpriteRenderer.h"
#include "Modules/SceneModule.h" // Ajout indispensable
#include "Core/Scene.h"           // Ajout indispensable
#include <iostream>

void Health::Update(float _deltaTime)
{
    // On ne gère le clignotement que si l'invulnérabilité est active (utile surtout pour le Player)
    if (isInvulnerable)
    {
        invulnerabilityTimer -= _deltaTime;
        auto* renderer = GetOwner()->GetComponent<SpriteRenderer>();

        if (renderer)
        {
            if ((int)(invulnerabilityTimer * 10) % 2 == 0)
                renderer->SetColor(sf::Color(255, 255, 255, 100));
            else
                renderer->SetColor(sf::Color(255, 255, 255, 255));
        }

        if (invulnerabilityTimer <= 0.0f)
        {
            isInvulnerable = false;
            if (renderer) renderer->SetColor(sf::Color(255, 255, 255, 255));
        }
    }
}

void Health::TakeDamage(int _amount)
{
    if (isInvulnerable) return;

    currentHealth -= _amount;
    std::cout << GetOwner()->GetName() << " blesse ! Vie : " << currentHealth << std::endl;

    if (currentHealth <= 0)
    {
        if (GetOwner()->GetName() == "Player")
        {
            std::cout << "GAME OVER" << std::endl;
            Engine::GetInstance()->RequestQuit();
        }
        else
        {
            // --- DESTRUCTION PAR AUTORITÉ ---
            auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
            if (sm)
            {
                Scene* scene = sm->GetSceneByName("BulletHell");
                if (scene)
                {
                    std::cout << "Mort de l'ennemi confirmee dans BulletHell" << std::endl;
                    scene->DestroyGameObject(GetOwner());
                    return;
                }
            }

            // Sécurité au cas où la scène n'est pas trouvée
            GetOwner()->Destroy();
        }
        return;
    }

    if (GetOwner()->GetName() == "Player")
    {
        isInvulnerable = true;
        invulnerabilityTimer = invulnerabilityDuration;
    }
}