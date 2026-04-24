#pragma once

#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Core/GameObject.h"

class Scene
{
public:


    explicit Scene(const std::string& _name, bool _enabled_at_start = true);
    virtual ~Scene() = default;

    void Awake() const;
    void Start() const;
    virtual void Update(const float _delta_time);

    void PreRender() const;
    void Render(sf::RenderWindow* _window) const;
    void OnGUI() const;
    void OnDebug() const;
    void OnDebugSelected() const;
    void PostRender() const;
    void Present() const;

    void OnEnable() const;
    void OnDisable() const;

    void Destroy() const;
    void Finalize() const;

    const std::string& GetName() const;

    GameObject* CreateGameObject(const std::string& _name);

    GameObject* FindGameObject(const std::string& _name) const;
    const std::vector<std::unique_ptr<GameObject>>& GetGameObjects() const;

    void DestroyGameObject(const GameObject* _game_object);

    void Enable();
    void Disable();

    bool IsEnabled() const;

    void MarkForDeletion();
    bool IsMarkedForDeletion() const;

private:
    std::string name;

    // La liste principale
    std::vector<std::unique_ptr<GameObject>> gameObjects;

    // --- LES NOUVELLES LISTES DE SÉCURITÉ ---
    // Objets en attente de création (pour la frame suivante)
    std::vector<std::unique_ptr<GameObject>> pendingObjects;

    // Objets en attente de suppression
    std::vector<const GameObject*> objectsToDestroy;

    bool enabled = true;
    bool markedForDeletion = false;
};

typedef std::unique_ptr<Scene> ScenePtr;

template<typename SceneType>
concept IsScene = std::derived_from<SceneType, Scene>;
