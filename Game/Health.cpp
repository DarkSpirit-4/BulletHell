#include "Health.h"
#include "Core/GameObject.h"
#include "Engine.h"
#include "Components/SpriteRenderer.h" // Vérifie bien le chemin de l'include
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
    // 1. Sécurité Invulnérabilité
    if (isInvulnerable) return;

    currentHealth -= _amount;
    std::cout << GetOwner()->GetName() << " blesse ! Vie : " << currentHealth << std::endl;

    // 2. Vérification de la mort
    if (currentHealth <= 0)
    {
        if (GetOwner()->GetName() == "Player")
        {
            std::cout << "GAME OVER" << std::endl;
            Engine::GetInstance()->RequestQuit();
        }
        else
        {
            // L'ennemi disparaît enfin
            GetOwner()->Destroy();
        }
        return; // On arrête la fonction ici si l'objet est mort
    }

    // 3. Application de l'invulnérabilité UNIQUEMENT pour le Player
    // On ne veut pas que les ennemis soient invulnérables, sinon on ne peut pas les "spammer" de balles
    if (GetOwner()->GetName() == "Player")
    {
        isInvulnerable = true;
        invulnerabilityTimer = invulnerabilityDuration;
    }
}