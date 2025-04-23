#pragma once
#define TEST_BITD(value, bit) ((value) & (1U << (bit)))
#define LODWORD(x) (*((uint32_t*)&(x)))

namespace offsets {
    inline uint64_t Il2CppGetHandle = 0xBF45AD0;
    inline uint64_t BaseNetworkable =  0xBCA9B50;
    inline uint64_t BaseNetworkable1 = 0x10;
    inline uint64_t BaseNetworkable2 = 0x10;
    inline uint64_t BaseNetworkable3 = 0x18;
    inline uint64_t BasePlayer =  0xBCF06D0;
    inline uint64_t PlayerList =  0x13C0;
    inline uint64_t MainCamera = 0xBC94C10; // 0x30
    inline uint64_t MainCamera1 = 0x30;
    inline uint64_t TOD_Sky = 0xBCA0848;
    inline uint64_t SingletonComponent = 0xBC40470;
    inline uint64_t ConsoleSystem = 0xBCCB550;
    inline uint64_t OcclusionCulling = 0xBCF9138;
    inline uint64_t FacepunchInput = 0xBCCFE60; // 0x48;
    
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
    inline uint64_t Belt = 0x58;
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
                    ecx = *(uint32_t*)(rdx);
                    eax = *(uint32_t*)(rdx);
                    rdx = (uint64_t*)((uint8_t*)rdx + 0x4);
                    eax = eax << 0x16;
                    ecx = ecx >> 0xA;
                    ecx = ecx | eax;
                    ecx = ecx + 0x271BE1AF;
                    eax = ecx;
                    ecx = ecx << 0xB;
                    eax = eax >> 0x15;
                    eax = eax | ecx;
                    eax = eax - 0x50967E36;
                    *((uint32_t*)rdx - 0x1) = eax;
                    --r8d;
            } while (r8d);
            return Il2cppGetHandle(rax);
    }
    
    inline uint64_t BaseNetworkable2(uint64_t address)
    {
            uint64_t rax = mem.Read<uint64_t>(address + 0x18);
            uint64_t* rdx = &rax;
            uint32_t r8d = 0x2;
            uint32_t eax, ecx, edx;
    
            do {
                    eax = *(uint32_t*)(rdx);
                    rdx = (uint64_t*)((uint8_t*)rdx + 0x4);
                    eax = eax + 0x53F27701;
                    ecx = eax;
                    eax = eax << 0x1C;
                    ecx = ecx >> 0x4;
                    ecx = ecx | eax;
                    ecx = ecx + 0x566650E2;
                    eax = ecx;
                    ecx = ecx << 0x15;
                    eax = eax >> 0xB;
                    eax = eax | ecx;
                    *((uint32_t*)rdx - 0x1) = eax;
                    --r8d;
            } while (r8d);
            return Il2cppGetHandle(rax);
    }
    
    inline uint64_t PlayerInventory(uint64_t address)
    {
            uint64_t rax = mem.Read<uint64_t>(address + 0x18);
            uint64_t* rdx = &rax;
            uint32_t r8d = 0x2;
            uint32_t eax, ecx, edx;
    
            do {
                    ecx = *(uint32_t*)(rdx);
                    eax = *(uint32_t*)(rdx);
                    rdx = (uint64_t*)((uint8_t*)rdx + 0x4);
                    ecx = ecx >> 0x9;
                    eax = eax << 0x17;
                    ecx = ecx | eax;
                    ecx = ecx ^ 0x2D9DE272;
                    ecx = ecx + 0x6A831A49;
                    ecx = ecx ^ 0x80042B5A;
                    *((uint32_t*)rdx - 0x1) = ecx;
                    --r8d;
            } while (r8d);
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
                    eax = eax + 0x2736DED8;
                    ecx = eax;
                    eax = eax << 0x7;
                    ecx = ecx >> 0x19;
                    ecx = ecx | eax;
                    ecx = ecx - 0xA584D0C;
                    *((uint32_t*)rdx - 0x1) = ecx;
                    --r8d;
            } while (r8d);
            return Il2cppGetHandle(rax);
    }
    
    inline uint64_t ClActiveItem(uint64_t address)
    {
    
            uint64_t rsp = address;
            uint64_t* rdx = &rsp;
            uint32_t r8d = 0x2;
            uint32_t eax, ecx, edx;
    
            do {
                    ecx = *(uint32_t*)(rdx);
                    eax = *(uint32_t*)(rdx);
                    rdx = (uint64_t*)((uint8_t*)rdx + 0x4);
                    eax = eax << 0x7;
                    ecx = ecx >> 0x19;
                    ecx = ecx | eax;
                    ecx = ecx + 0x84F2A697;
                    eax = ecx;
                    ecx = ecx << 0xA;
                    eax = eax >> 0x16;
                    eax = eax | ecx;
                    eax = eax - 0x654AA38E;
                    *((uint32_t*)rdx - 0x1) = eax;
                    --r8d;
            } while (r8d);
            return rsp;
    }
}
