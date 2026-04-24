#include "ClickerLogic.h"
#include "Core/GameObject.h"
#include "Engine.h"
#include "Modules/InputModule.h"
#include "Modules/WindowModule.h"
#include <imgui.h>
#include <iostream>
#include <string>
#include <cstdlib>

void ClickerLogic::Update(float _dt)
{
    auto* mm = Engine::GetInstance()->GetModuleManager();
    auto* input = mm->GetModule<InputModule>();
    auto* windowMod = mm->GetModule<WindowModule>();

    if (!input || !windowMod) return;

    sf::RenderWindow* window = windowMod->GetWindow();

    if (input->GetMouseButtonDown(sf::Mouse::Button::Left))
    {
        if (can_Click)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
            sf::Vector2f worldPos = window->mapPixelToCoords(pixelPos);

            Maths::Vector2f pos = GetOwner()->GetPosition();
            float halfSize = 32.0f;

            if (worldPos.x >= pos.x - halfSize && worldPos.x <= pos.x + halfSize &&
                worldPos.y >= pos.y - halfSize && worldPos.y <= pos.y + halfSize)
            {
                // Gain d'argent classique
                m_money++;

                // Chance de gagner une gemme
                if (std::rand() % 75 == 0)
                {
                    m_gems++;
                    std::cout << "[LUCKY] +1 Gemme ! Total : " << m_gems << std::endl;
                }

                GetOwner()->SetScale(Maths::Vector2f(1.15f, 1.15f));

                std::cout << "[CLICKER] +1 Argent ! Total : " << m_money << std::endl;
            }
            can_Click = false;
        }
    }
    else
    {
        can_Click = true;

        Maths::Vector2f currentScale = GetOwner()->GetScale();
        if (currentScale.x > 1.0f)
        {
            float newScale = currentScale.x - (2.0f * _dt);
            if (newScale < 1.0f) newScale = 1.0f;
            GetOwner()->SetScale(Maths::Vector2f(newScale, newScale));
        }
    }
}

void ClickerLogic::OnGUI()
{
    float windowWidth = ImGui::GetIO().DisplaySize.x;

    ImGui::SetNextWindowPos(ImVec2(windowWidth - 650, 20), ImGuiCond_Always);

    ImGui::SetNextWindowSize(ImVec2(220, 120), ImGuiCond_Always);

    ImGui::Begin("ClickerUI", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBackground |
        ImGuiWindowFlags_NoScrollbar);

    ImGui::SetWindowFontScale(2.5f);
    ImGui::TextColored(ImVec4(1.0f, 0.84f, 0.0f, 1.0f), "$ %d", m_money);

    ImGui::SetWindowFontScale(2.5f);
    ImGui::TextColored(ImVec4(0.0f, 0.9f, 1.0f, 1.0f), "V %d", m_gems);

    ImGui::End();
}