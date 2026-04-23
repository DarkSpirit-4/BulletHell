#include "HealthBar.h"
#include "Health.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Components/RectangleShapeRenderer.h"

void HealthBar::Start()
{
    auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    Scene* scene = sm->GetScenesList().front().get();

    // On crée 5 GameObjects pour représenter les 5 PV
    for (int i = 0; i < 5; ++i)
    {
        GameObject* h = scene->CreateGameObject("HeartIndicator");
        // Position en haut à droite : x = 650, 680, 710...
        h->SetPosition(Maths::Vector2f(500.f + (i * 30.f), 30.f));

        // On lui donne un visuel via ton moteur
        auto* renderer = h->CreateComponent<RectangleShapeRenderer>();
        renderer->SetSize(Maths::Vector2f(20.f, 20.f));
        renderer->SetColor(sf::Color::Red);

        hearts.push_back(h);
    }
}

void HealthBar::Update(float dt)
{
    auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    Scene* scene = sm->GetScenesList().front().get();

    GameObject* player = scene->FindGameObject("Player");
    if (!player) return;

    auto* hp = player->GetComponent<Health>();
    if (!hp) return;

    // Si les PV ont changé, on met à jour la visibilité
    for (int i = 0; i < (int)hearts.size(); ++i)
    {
        // Si l'index est inférieur aux PV actuels, on affiche, sinon on cache
        // Note : Si ton moteur n'a pas SetActive, on peut changer la couleur en transparent
        if (i < hp->currentHealth)
            hearts[i]->GetComponent<RectangleShapeRenderer>()->SetColor(sf::Color::Red);
        else
            hearts[i]->GetComponent<RectangleShapeRenderer>()->SetColor(sf::Color::Transparent);
    }
}