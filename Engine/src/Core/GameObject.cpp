#include "Core/GameObject.h"
#include "Core/Scene.h"         // <--- AJOUTE CET INCLUDE
#include "Engine.h"             // <--- AJOUTE CET INCLUDE
#include "Modules/SceneModule.h" // <--- AJOUTE CET INCLUDE (pour trouver la scène)

GameObject::~GameObject()
{
    for (Component*& component : components)
        delete component;

    components.clear();
}

std::vector<Component*>& GameObject::GetComponents()
{
    return components;
}

void GameObject::AddComponent(Component* _component)
{
    _component->SetOwner(this);
    components.push_back(_component);
}

void GameObject::RemoveComponent(Component* _component)
{
    std::erase(components, _component);
}

#pragma region Events

void GameObject::Awake() const
{
    for (Component* const& component : components)
    {
        component->Awake();
    }
}

void GameObject::Start() const
{
    for (Component* const& component : components)
    {
        component->Start();
    }
}

void GameObject::Update(const float _delta_time) const
{
    for (Component* const& component : components)
    {
        component->Update(_delta_time);
    }
}

void GameObject::PreRender() const
{
    for (Component* const& component : components)
    {
        component->PreRender();
    }
}

void GameObject::Render(sf::RenderWindow* _window) const
{
    for (Component* const& component : components)
    {
        component->Render(_window);
    }
}

void GameObject::OnGUI() const
{
    for (Component* const& component : components)
    {
        component->OnGUI();
    }
}

void GameObject::PostRender() const
{
    for (Component* const& component : components)
    {
        component->PostRender();
    }
}

void GameObject::OnDebug() const
{
    for (Component* const& component : components)
    {
        component->OnDebug();
    }
}

void GameObject::OnDebugSelected() const
{
    for (Component* const& component : components)
    {
        component->OnDebugSelected();
    }
}

void GameObject::Present() const
{
    for (Component* const& component : components)
    {
        component->Present();
    }
}

void GameObject::OnEnable() const
{
    for (Component* const& component : components)
    {
        component->OnEnable();
    }
}

void GameObject::OnDisable() const
{
    for (Component* const& component : components)
    {
        component->OnDisable();
    }
}

void GameObject::Destroy() const
{
    // 1. On prévient les composants (ton code actuel)
    for (Component* const& component : components)
    {
        component->Destroy();
    }

    // 2. ON PRÉVIENT LA SCÈNE ! (Le chaînon manquant)
    auto* sm = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
    if (sm && !sm->GetScenesList().empty()) {
        Scene* currentScene = sm->GetScenesList().front().get();
        currentScene->DestroyGameObject(this);
    }
}

void GameObject::Finalize() const
{
    for (Component* const& component : components)
    {
        component->Finalize();
    }
}

#pragma endregion
