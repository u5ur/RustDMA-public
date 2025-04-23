#include "core.h"

void Helper::DrawSkeleton(Model::Transforms bones, Unity::Camera camera, ImColor color) {

    Vector2 Eye2d = camera.WorldToScreen(bones.Eye.GetPosition());
    Vector2 Head2d = camera.WorldToScreen(bones.Head.GetPosition());
    Vector2 Neck2d = camera.WorldToScreen(bones.Neck.GetPosition());
    Vector2 Spine2d = camera.WorldToScreen(bones.Spine.GetPosition());
    Vector2 Pelvis2d = camera.WorldToScreen(bones.Pelvis.GetPosition());
    Vector2 LShoulder = camera.WorldToScreen(bones.LShoulder.GetPosition());
    Vector2 LForeArm = camera.WorldToScreen(bones.LForeArm.GetPosition());
    Vector2 LHand = camera.WorldToScreen(bones.LHand.GetPosition());
    Vector2 RShoulder = camera.WorldToScreen(bones.RShoulder.GetPosition());
    Vector2 RForeArm = camera.WorldToScreen(bones.RForeArm.GetPosition());
    Vector2 RHand2d = camera.WorldToScreen(bones.RHand.GetPosition());
    Vector2 LHip2d = camera.WorldToScreen(bones.LHip.GetPosition());
    Vector2 LKnee2d = camera.WorldToScreen(bones.LKnee.GetPosition());
    Vector2 LFoot2d = camera.WorldToScreen(bones.LFoot.GetPosition());
    Vector2 RHip2d = camera.WorldToScreen(bones.RHip.GetPosition());
    Vector2 RKnee2d = camera.WorldToScreen(bones.RKnee.GetPosition());
    Vector2 RFoot2d = camera.WorldToScreen(bones.RFoot.GetPosition());

    ImGui::GetBackgroundDrawList()->AddLine({ Head2d.x, Head2d.y }, { Eye2d.x, Eye2d.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ Head2d.x, Head2d.y }, { Neck2d.x, Neck2d.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ Neck2d.x, Neck2d.y }, { Spine2d.x, Spine2d.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ Spine2d.x, Spine2d.y }, { Pelvis2d.x, Pelvis2d.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ Neck2d.x, Neck2d.y }, { LShoulder.x, LShoulder.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ LShoulder.x, LShoulder.y }, { LForeArm.x, LForeArm.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ LForeArm.x, LForeArm.y }, { LHand.x, LHand.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ Neck2d.x, Neck2d.y }, { RShoulder.x, RShoulder.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ RShoulder.x, RShoulder.y }, { RForeArm.x, RForeArm.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ RForeArm.x, RForeArm.y }, { RHand2d.x, RHand2d.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ Pelvis2d.x, Pelvis2d.y }, { LHip2d.x, LHip2d.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ LHip2d.x, LHip2d.y }, { LKnee2d.x, LKnee2d.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ LKnee2d.x, LKnee2d.y }, { LFoot2d.x, LFoot2d.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ Pelvis2d.x, Pelvis2d.y }, { RHip2d.x, RHip2d.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ RHip2d.x, RHip2d.y }, { RKnee2d.x, RKnee2d.y }, color, 1.0f);
    ImGui::GetBackgroundDrawList()->AddLine({ RKnee2d.x, RKnee2d.y }, { RFoot2d.x, RFoot2d.y }, color, 1.0f);
}

std::vector<std::string> Helper::GetPlayerInventory(BasePlayer player)
{
    uint64_t Inventory = Decrypt::PlayerInventory(mem.Read<uint64_t>(player.Address + offsets::PlayerInventory));
    if (!Inventory) return {};

    uint64_t Belt = mem.Read<uint64_t>(Inventory + offsets::Belt);
    if (!Belt) return {};

    uint64_t ItemList = mem.Read<uint64_t>(Belt + offsets::ItemList);
    if (!ItemList) return {};

    uint64_t List = mem.Read<uint64_t>(ItemList + 0x10);
    if (!List) return {};

    uint32_t Size = mem.Read<uint32_t>(List + 0x18);
    if (Size <= 0 || Size >= 1000) return {};

    std::vector<std::string> Names(Size);

    for (int i = 0; i < Size; i++)
    {
        uint64_t Item = mem.Read<uint64_t>(List + (0x20 + (i * 0x8)));
        if (!Item) continue;

        uint64_t ItemDef = mem.Read<uint64_t>(Item + offsets::ItemDefinition);
        if (!ItemDef) continue;

        auto ShortName = mem.Read<Unity::String>(mem.Read<uint64_t>(ItemDef + 0x28));
        if (ShortName.size <= 0 || ShortName.size > 1000) continue;

        std::wstring WName(std::wstring(ShortName.str, ShortName.size));
        std::string Name{ WName.begin(), WName.end() };
        if (Name.empty()) continue;

        Names.push_back(Name);

    }

    return Names;
}