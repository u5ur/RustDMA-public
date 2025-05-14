#pragma once
#define TEST_BITD(value, bit) ((value) & (1U << (bit)))
#define LODWORD(x) (*((uint32_t*)&(x)))

namespace offsets {
    inline uint64_t Il2CppGetHandle = 0xC057BA0;
    inline uint64_t BaseNetworkable = 0xBDB0D38;
    inline uint64_t BaseNetworkable1 = 0x10;
    inline uint64_t BaseNetworkable2 = 0x10;
    inline uint64_t BaseNetworkable3 = 0x20;
    inline uint64_t BasePlayer = 0xBDCEE68;
    inline uint64_t PlayerList = 0xBB8;
    inline uint64_t MainCamera = 0xBDB0B78; // 0x60
    inline uint64_t MainCamera1 = 0x60;
    inline uint64_t TOD_Sky = 0xBDB67A0;
    inline uint64_t SingletonComponent = 0xBD45498;
    inline uint64_t OcclusionCulling = 0xBDD4D78;
    inline uint64_t ConvarGraphics = 0xBD53580;
    inline uint64_t ConvarAdmin = 0xBE02638;
    inline uint64_t ConsoleSystem = 0xBDA4B28; // 0x88;
    inline uint64_t FacepunchInput = 0xBDA9040; // 0x150;
    inline uint64_t UpdateAmbient = 0xB1B480;

    // BasePlayer
    inline uint64_t ClActiveItem = 0x460;
    inline uint64_t PlayerEyes = 0x478;
    inline uint64_t PlayerInventory = 0x3E0;
    inline uint64_t CurrrentTeam = 0x430;
    inline uint64_t BaseMovement = 0x588;
    inline uint64_t PlayerModel = 0x5B0;
    inline uint64_t PlayerFlags = 0x558;
    inline uint64_t DisplayName = 0x3F8;
    inline uint64_t PlayerInput = 0x568;

    // PlayerModel
    inline uint64_t SkinnedMultiMesh = 0x278;

    // SkinnedMultiMesh
    inline uint64_t RendererList = 0x40;

    // PlayerInventory
    inline uint64_t Belt = 0x28;
    inline uint64_t Wear = 0x30;

    // ItemContainer
    inline uint64_t ItemList = 0x38;

    // Item
    inline uint64_t Health = 0x88;
    inline uint64_t MaxHealth = 0xB0;
    inline uint64_t Amount = 0x28;
    inline uint64_t ItemDefinition = 0x60;
    inline uint64_t HeldItem = 0x70;
    inline uint64_t ItemId = 0xC8;

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
    inline uint64_t IsDown = 0x2C;
    inline uint64_t Name = 0x38;
    inline uint64_t Binds = 0x10;
    inline uint64_t Code = 0x28;

    inline uint64_t Fov = 0x490;

    inline uint64_t AdminTime = 0x48;
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

    inline uint64_t BaseNetworkable1(uint64_t address)
    {
        uint64_t rax = mem.Read<uint64_t>(address + 0x18);
        uint64_t* rdx = &rax;
        uint32_t r8d = 0x2;
        uint32_t eax, ecx, edx;

        do {
            eax = *(uint32_t*)(rdx);
            rdx = (uint64_t*)((uint8_t*)rdx + 0x4);
            eax = eax - 0x2264152;
            eax = eax ^ 0x73999BB1;
            eax = eax + 0x2B48BC2F;
            ecx = eax;
            eax = eax + eax;
            ecx = ecx >> 0x1F;
            ecx = ecx | eax;
            *((uint32_t*)rdx - 0x1) = ecx;
            --r8d;
        } while (r8d);
        return Il2cppGetHandle(rax);
    }

    inline uint64_t BaseNetworkable2(uint64_t address)
    {
        uint64_t rax = mem.Read<uint64_t>(address + 0x18);
        uint64_t* rcx = &rax;
        uint32_t edx = 0x2;
        uint32_t eax, ecx;

        do {
            eax = *(uint32_t*)(rcx);
            rcx = (uint64_t*)((uint8_t*)rcx + 0x4);
            eax = eax - 0x2EBBD4AE;
            eax = eax ^ 0xA406ACCA;
            eax = eax + 0x36165F78;
            eax = eax ^ 0xB6679C03;
            *((uint32_t*)rcx - 0x1) = eax;
            --edx;
        } while (edx);
        return Il2cppGetHandle(rax);
    }

    inline uint64_t PlayerInventory(uint64_t address)
    {
        uint64_t rax = mem.Read<uint64_t>(address + 0x18);
        uint64_t* r8 = &rax;
        uint32_t r9d = 0x2;
        uint32_t eax, ecx, edx;

        do {
            edx = *(uint32_t*)(r8);
            eax = *(uint32_t*)(r8);
            r8 = (uint64_t*)((uint8_t*)r8 + 0x4);
            edx = edx >> 0x14;
            eax = eax << 0xC;
            edx = edx | eax;
            edx = edx - 0x795F0C57;
            edx = edx ^ 0xB392FC62;
            ecx = edx;
            ecx = ecx >> 0x1F;
            eax = (edx + edx);
            ecx = ecx | eax;
            *((uint32_t*)r8 - 0x1) = ecx;
            --r9d;
        } while (r9d);
        return Il2cppGetHandle(rax);
    }

    inline uint64_t PlayerEyes(uint64_t address)
    {
        uint64_t rax = mem.Read<uint64_t>(address + 0x18);
        uint64_t* rdx = &rax;
        uint32_t r8d = 0x2;
        uint32_t eax, ecx, edx;

        do {
            eax = *(uint32_t*)(rdx);
            rdx = (uint64_t*)((uint8_t*)rdx + 0x4);
            eax = eax + 0x8EBF4508;
            ecx = eax;
            eax = eax << 0x8;
            ecx = ecx >> 0x18;
            ecx = ecx | eax;
            ecx = ecx ^ 0x23E2D133;
            eax = ecx;
            ecx = ecx << 0x15;
            eax = eax >> 0xB;
            eax = eax | ecx;
            *((uint32_t*)rdx - 0x1) = eax;
            --r8d;
        } while (r8d);
        return Il2cppGetHandle(rax);
    }

    inline uint64_t ClActiveItem(uint64_t address)
    {
        uint64_t rsp = address;
        uint64_t* rax = &rsp;
        uint32_t r8d = 0x2;
        uint32_t eax, ecx, edx;

        do {
            edx = *(uint32_t*)(rax);
            ecx = *(uint32_t*)(rax);
            rax = (uint64_t*)((uint8_t*)rax + 0x4);
            edx = edx >> 0x7;
            ecx = ecx << 0x19;
            edx = edx | ecx;
            edx = edx ^ 0x506DB171;
            edx = edx + 0x345C3967;
            edx = edx ^ 0x87DEA084;
            *((uint32_t*)rax - 0x1) = edx;
            --r8d;
        } while (r8d);
        return rsp;
    }

}
