#pragma once

#include "Core/Component.h"
#include <SFML/System/Vector2.hpp>

class ClickerLogic final : public Component
{
public:
    void Update(float _dt) override;
    void OnGUI() override;

    int GetMoney() const { return m_money; }

private:
    int m_money = 0;
    int m_gems = 0;
    bool can_Click = true;
};