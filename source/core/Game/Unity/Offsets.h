#pragma once
#define TEST_BITD(value, bit) ((value) & (1U << (bit)))
#define LODWORD(x) (*((uint32_t*)&(x)))

namespace offsets {
    const uint64_t Il2CppGetHandle = 0xBF45AD0;
    const uint64_t BaseNetworkable = 0xBCA9B50;
    inline uint64_t BaseNetworkable1 = 0x10;
    inline uint64_t BaseNetworkable2 = 0x10;
    inline uint64_t BaseNetworkable3 = 0x18;
    inline uint64_t MainCamera = 0xBC94C10; // 0x30
    inline uint64_t MainCamera1 = 0x30;
    inline uint64_t TOD_Sky = 0xBCA0848;
    inline uint64_t SingletonComponent = 0xBC40470;
    inline uint64_t ConsoleSystem = 0xBCCB550;
    inline uint64_t OcclusionCulling = 0xBCF9138;
    inline uint64_t FacepunchInput = 0xBCCFE60; // 0x48;
    inline uint64_t Buttons = 0x48;

    // BasePlayer
    inline uint64_t ClActiveItem = 0x458;
    inline uint64_t PlayerEyes = 0x648;
    inline uint64_t PlayerInventory = 0x590;
    inline uint64_t CurrrentTeam = 0x428;
    inline uint64_t BaseMovement = 0x300;
    inline uint64_t PlayerModel = 0x408;
    inline uint64_t PlayerFlags = 0x550;
    inline uint64_t DisplayName = 0x558;
    inline uint64_t PlayerInput = 0x328;

    // PlayerModel
    inline uint64_t SkinnedMultiMesh = 0x3C8;

    // SkinnedMultiMesh
    inline uint64_t RendererList = 0x58;

    // PlayerInventory
    inline uint64_t Belt = 0x38;
    inline uint64_t Wear = 0x60;

    // %8e84899c790cfa0b6ba4cc05d3f5871f0146c0e1 (ItemContainer)
    inline uint64_t ItemList = 0x60;

    // %e1ac09b7f113111b9b80a112c6358b07ced328b8 (Item)
    inline uint64_t Health = 0x48;
    inline uint64_t MaxHealth = 0x70;
    inline uint64_t Amount = 0x78;
    inline uint64_t ItemDefinition = 0xA8;
    inline uint64_t HeldItem = 0x18;
    inline uint64_t ItemId = 0x28;

    // BaseProjectile
    inline uint64_t RecoilProperties = 0x340;
    inline uint64_t PrimaryMagazine = 0x318;

    // RecoilProperties
    inline uint64_t NewRecoilOverride = 0x80;
    inline uint64_t RecoilYawMin = 0x18;
    inline uint64_t RecoilYawMax = 0x1C;
    inline uint64_t RecoilPitchMin = 0x20;
    inline uint64_t RecoilPitchMax = 0x24;

    // HeldEntity
    inline uint64_t ViewModel = 0x218;

    // Input.Button
    inline uint64_t IsDown = 0x28;
    inline uint64_t Name = 0x20;
    inline uint64_t Binds = 0x30;
    inline uint64_t Code = 0x1C;


    inline uint64_t AmmoCount = 0xDC;
}

namespace Decrypt
{
    inline uint64_t Il2cppGetHandle(int32_t ObjectHandleID) {

        if (!ObjectHandleID) return 0;

        uint64_t rdi_1 = ObjectHandleID >> 3;
        uint64_t rcx_1 = (ObjectHandleID & 7) - 1;
        uint64_t baseAddr = mem.BaseAddress + offsets::Il2CppGetHandle + rcx_1 * 0x28;
        uint32_t limit = mem.Read<uint32_t>(baseAddr + 0x10);
        if (rdi_1 < limit) {
            uint64_t objAddr = mem.Read<uint64_t>(baseAddr);
            uint32_t bitMask = mem.Read<uint32_t>(objAddr + ((rdi_1 >> 5) << 2));
            if (TEST_BITD(bitMask, rdi_1 & 0x1f)) {
                uintptr_t ObjectArray = mem.Read<uint64_t>(baseAddr + 0x8) + (rdi_1 << 3);
                uint64_t result = mem.Read<BYTE>(baseAddr + 0x14) > 1
                    ? mem.Read<uint64_t>(ObjectArray)
                    : ~mem.Read<uint32_t>(ObjectArray);

                return result;
            }
        }

        return 0;
    }

    inline uint64_t BaseNetworkable1(uint64_t Address)
    {
        uint64_t v1 = mem.Read<uint64_t>(Address + 0x18);
        uint64_t* v2 = &v1;
        int v3 = 0x02;
        unsigned int v4, v5;
        do
        {
            v4 = *(unsigned int*)v2;
            v2 = (uint64_t*)((char*)v2 + 0x04);
            v5 = v4;
            v4 = v4;
            v4 = v4 << 0x16;
            v5 = v5 >> 0x0A;
            v5 = v5 | v4;
            v5 = v5 + 0x271BE1AF;
            v4 = v5;
            v5 = v5 << 0x0B;
            v4 = v4 >> 0x15;
            v4 = v4 | v5;
            v4 = v4 - 0x50967E36;
            *((unsigned int*)v2 - 1) = v4;
            --v3;
        } while (v3);

        return Il2cppGetHandle(v1);
    }

    inline uint64_t BaseNetworkable2(uint64_t Address)
    {
        uint64_t v1 = mem.Read<uint64_t>(Address + 0x18);
        uint64_t* v2 = &v1;
        int v3 = 0x02;
        unsigned int v4, v5;
        do
        {
            v4 = *(unsigned int*)v2;
            v2 = (uint64_t*)((char*)v2 + 0x04);
            v4 = v4;
            v4 = v4 + 0x53F27701;
            v5 = v4;
            v4 = v4 << 0x1C;
            v5 = v5 >> 0x04;
            v5 = v5 | v4;
            v5 = v5 + 0x566650E2;
            v4 = v5;
            v5 = v5 << 0x15;
            v4 = v4 >> 0x0B;
            v4 = v4 | v5;
            *((unsigned int*)v2 - 1) = v4;
            --v3;
        } while (v3);

        return Il2cppGetHandle(v1);
    }

    inline uint64_t PlayerInventory(uint64_t Address)
    {
        uint64_t v1 = mem.Read<uint64_t>(Address + 0x18);
        uint64_t* v2 = &v1;
        int v3 = 0x02;
        unsigned int v4, v5;
        do
        {
            v4 = *(unsigned int*)v2;
            v2 = (uint64_t*)((char*)v2 + 0x04);
            v5 = v4;
            v4 = v4;
            v5 = v5 >> 0x09;
            v4 = v4 << 0x17;
            v5 = v5 | v4;
            v5 = v5 ^ 0x2D9DE272;
            v5 = v5 + 0x6A831A49;
            v5 = v5 ^ 0x80042B5A;
            *((unsigned int*)v2 - 1) = v5;
            --v3;
        } while (v3);

        return Il2cppGetHandle(v1);
    }

    inline uint64_t PlayerEyes(uint64_t Address)
    {
        uint64_t v1 = mem.Read<uint64_t>(Address + 0x18);
        uint64_t* v2 = &v1;
        int v3 = 0x02;
        unsigned int v4, v5;
        do
        {
            v4 = *(unsigned int*)v2;
            v2 = (uint64_t*)((char*)v2 + 0x04);
            v4 = v4;
            v4 = v4 + 0x2736DED8;
            v5 = v4;
            v4 = v4 << 0x07;
            v5 = v5 >> 0x19;
            v5 = v5 | v4;
            v5 = v5 - 0xA584D0C;
            *((unsigned int*)v2 - 1) = v5;
            --v3;
        } while (v3);

        return Il2cppGetHandle(v1);
    }
}