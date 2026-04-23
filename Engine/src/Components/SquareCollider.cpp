#include "Components/SquareCollider.h"
#include "Components/RectangleShapeRenderer.h"

#include "Core/GameObject.h"
#include "Maths/Vector2.h"

bool SquareCollider::IsColliding(const SquareCollider& _collider_a, const SquareCollider& _collider_b)
{
    const Maths::Vector2f position_a = _collider_a.GetOwner()->GetPosition();
    const Maths::Vector2f position_b = _collider_b.GetOwner()->GetPosition();
    return position_a.x < position_b.x + _collider_b.GetWidth() && position_a.x + _collider_a.GetWidth() > position_b.x
        && position_a.y < position_b.y + _collider_b.GetHeight() && position_a.y + _collider_a.GetHeight() > position_b.
        y;
}

void SquareCollider::DebugRender(sf::RenderWindow* _window) //ajout
{
    // On crée une forme rectangulaire SFML
    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(width, height));

    // On la rend transparente à l'intérieur avec un contour vert
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Green); // Vert = Hitbox active
    shape.setOutlineThickness(2.0f);

    // IMPORTANT : Aligner la hitbox avec la position du GameObject
    // Si tes sprites sont centrés, n'oublie pas de décaler le dessin de la hitbox
    // pour qu'elle soit centrée aussi (origine au milieu)
    shape.setOrigin(sf::Vector2f(width * 0.5f, height * 0.5f));

    shape.setPosition(static_cast<sf::Vector2f>(GetOwner()->GetPosition()));
    shape.setRotation(GetOwner()->GetRotation());

    _window->draw(shape);
}
