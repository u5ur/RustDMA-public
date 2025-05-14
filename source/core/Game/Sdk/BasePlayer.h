#pragma once

class BasePlayer
{
private:

public:

    uint64_t Address = 0;

	static uint64_t GetPlayerList()
	{
		uint64_t TypeInfo = mem.Read<uint64_t>(mem.BaseAddress + offsets::BasePlayer);
        if (!TypeInfo) return 0;

		uint64_t StaticFields = mem.Read<uint64_t>(TypeInfo + 0xb8);
        if (!StaticFields) return 0;

        auto Dict = Decrypt::BaseNetworkable1(mem.Read<uint64_t>(StaticFields + offsets::PlayerList));
        if (!Dict) return 0;

        return mem.Read<uint64_t>(Dict + 0x20);
	}

    bool IsLocalPlayer = false;
    uint64_t DisplayNamePtr;
    Unity::String DisplayName = {};
    Model model;
};
