#include "Enemy.h"
#include "Core/GameObject.h"

void Enemy::Update(float _deltaTime)
{
    // Déplacement en ligne droite
    Maths::Vector2f pos = GetOwner()->GetPosition();
    pos.x += direction.x * speed * _deltaTime;
    pos.y += direction.y * speed * _deltaTime;
    GetOwner()->SetPosition(pos);

    // Suppression si l'ennemi sort largement de l'écran (ex: 800x800)
    if (pos.x < -100 || pos.x > 900 || pos.y < -100 || pos.y > 900)
    {
        GetOwner()->Destroy();
    }
}