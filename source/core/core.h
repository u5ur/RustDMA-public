#pragma once
#include "Render/render.h"
#include "Game/update.h"

namespace Helper
{
    void DrawSkeleton(Model::Transforms& bones, Unity::Camera& camera, ImColor color);
    std::vector<std::string> GetPlayerInventory(BasePlayer& player);
}

static void RenderPlayers()
{
    std::lock_guard<std::mutex> lock(playersMutex);
    if (Players.empty()) return;

    float MinScreenDistance = std::numeric_limits<float>::max();
    float MinMeterDistance = std::numeric_limits<float>::max();

    BasePlayer ClosestPlayer = {};

    for (auto& player : Players)
    {
        if (player.IsLocalPlayer) continue;

        Vector3 Head3d = player.model.transforms.Head.GetPosition();
        if (Head3d.Empty()) continue;

        Vector2 Head2d = Camera.WorldToScreen(Head3d);
        if (Head2d.Empty()) continue;

        Vector3 Root3d = (player.model.transforms.RFoot.GetPosition() + player.model.transforms.LFoot.GetPosition()) * 0.5f;
        if (Root3d.Empty()) continue;

        Vector2 Root2d = Camera.WorldToScreen(Root3d);
        if (Root2d.Empty()) continue;

        float Distance = Camera.Location.Distance(Head3d);
        if (Distance >= 300 || Distance <= 0) continue;

        Helper::DrawSkeleton(player.model.transforms, Camera, ImColor(255, 255, 255, 255));

        std::wstring WName(std::wstring(player.DisplayName.str, player.DisplayName.size));
        std::string Name{ WName.begin(), WName.end() };

        float yOffset = std::clamp(150.0f / Distance, 15.0f, 20.0f);
        ImVec2 textSize = ImGui::CalcTextSize(Name.c_str());
        ImVec2 textPos = ImVec2(Head2d.x - textSize.x * 0.5f, Head2d.y - yOffset);
        ImGui::GetBackgroundDrawList()->AddText(textPos, IM_COL32(255, 255, 255, 255), Name.c_str());


        float dx = Head2d.x - (1920 / 2.0f);
        float dy = Head2d.y - (1080 / 2.0f);
        float ScreenDist = std::sqrt(dx * dx + dy * dy);

        if (ScreenDist <= 100 &&
            ScreenDist < MinScreenDistance)
        {
            MinScreenDistance = ScreenDist;

            if (Distance < MinMeterDistance)
            {
                MinMeterDistance = Distance;
                ClosestPlayer = player;
            }
        }
    }

    if (ClosestPlayer.Address)
    {
        auto Names = Helper::GetPlayerInventory(ClosestPlayer);
        if (!Names.empty())
        {
            float Y = 30.0f;
            float spacing = 10.0f;

            float totalWidth = 0.0f;
            for (const auto& name : Names)
                totalWidth += ImGui::CalcTextSize(name.c_str()).x + spacing;
            totalWidth -= spacing;

            float X = (1920.0f - totalWidth) / 2.0f;

            for (const auto& name : Names)
            {
                ImVec2 textSize = ImGui::CalcTextSize(name.c_str());
                ImGui::GetBackgroundDrawList()->AddText(ImVec2(X, Y), IM_COL32(255, 255, 255, 255), name.c_str());
                X += textSize.x + spacing;
            }
        }
    }
}
