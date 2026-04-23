#include "Shooter.h"
#include "Bullet.h"
#include "Core/GameObject.h"
#include "Engine.h"
#include "Modules/SceneModule.h"
#include "SquareCollider.h"
#include "Components/RectangleShapeRenderer.h"

void Shooter::Update(float deltaTime)
{
    timer += deltaTime;

    // 1. Vérification des entrées et du cooldown
    if (!InputModule::GetMouseButton(sf::Mouse::Button::Left) || timer < fireRate)
        return;

    // 2. Sécurité : on vérifie que le script est bien attaché à un objet
    GameObject* owner = GetOwner();
    if (!owner) return;

    timer = 0.0f;

    // Position du joueur
    auto pos = owner->GetPosition();

    // Direction vers la souris
    Maths::Vector2f mouse(
        (float)InputModule::GetMousePosition().x,
        (float)InputModule::GetMousePosition().y
    );

    Maths::Vector2f dir = mouse - pos;
    float len = dir.Magnitude();

    // Normalisation de la direction
    if (len > 0.1f)
        dir = dir / len;
    else
        dir = Maths::Vector2f(0.0f, -1.0f); // Tir par défaut vers le haut si la souris est sur le joueur

    // 3. Récupération de la scène
    SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    if (!sceneModule || sceneModule->GetScenesList().empty()) return;

    Scene* scene = sceneModule->GetScenesList().front().get();

    // 4. Création de la balle (Désormais SÛR grâce à ta modif moteur !)
    GameObject* bullet = scene->CreateGameObject("PlayerBullet");
    if (bullet)
    {
        bullet->SetPosition(pos);

        // Configuration de la logique Bullet
        Bullet* b = bullet->CreateComponent<Bullet>();
        if (b) {
            b->direction = dir;
            b->speed = 800.0f;    // Plus rapide que la pluie (qui est à 250)
            b->isEnemy = false;   // Badge "Ami"
        }

        // Apparence visuelle
        auto* renderer = bullet->CreateComponent<RectangleShapeRenderer>();
        if (renderer) {
            renderer->SetColor(sf::Color::Yellow);
            renderer->SetSize(Maths::Vector2f(10.f, 10.f));
        }

        // --- AJOUTER LA HITBOX ICI ---
        auto* col = bullet->CreateComponent<SquareCollider>();
        if (col) {
            col->SetWidth(10.0f);
            col->SetHeight(10.0f);
        }
    }
}