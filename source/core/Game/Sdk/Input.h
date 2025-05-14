#pragma once
#include <unordered_map>

class Input
{
public:

	class Button
	{
	private:

		bool bIsDown = false;

	public:

		uint64_t Address = 0;

		Button() = default;
		Button(uint64_t address) : Address(address) {}

		Unity::String GetName() const
		{
			if (!this->Address) return {};
			return mem.Read<Unity::String>(mem.Read<uint64_t>(this->Address + offsets::Name));
		}

		void UpdateIsDown(VMMDLL_SCATTER_HANDLE handle)
		{
			mem.AddScatterRead(handle, this->Address + offsets::IsDown, &this->bIsDown, sizeof(bool));
		}

		bool IsDown() const
		{
			return this->bIsDown;
		}

		Unity::KeyCode GetKeyCode() const
		{
			if (!this->Address) return Unity::KeyCode::Invalid;
			return mem.Read<Unity::KeyCode>(this->Address + offsets::Code);
		}
	};

	static std::unordered_map<Unity::KeyCode, Button> Keys;

	static uint64_t GetButtons()
	{
		uint64_t TypeInfo = mem.Read<uint64_t>(mem.BaseAddress + offsets::FacepunchInput);
		if (!TypeInfo) return 0;

		uint64_t StaticFields = mem.Read<uint64_t>(TypeInfo + 0xB8);
		if (!StaticFields) return 0;

		return mem.Read<uint64_t>(StaticFields + 0x150);
	}

	static void SetupButtons()
	{
		uint64_t Buttons = GetButtons();
		if (!Buttons) return;

		uint64_t List = mem.Read<uint64_t>(Buttons + 0x10);
		if (!List) return;

		uint32_t Size = mem.Read<uint32_t>(Buttons + 0x18);
		if (Size <= 0 || Size >= 100000) return;

		for (int i = 0; i < Size; i++)
		{
			Button button = mem.Read<uint64_t>(List + (0x20 + (i * 0x8)));
			if (!button.Address) continue;

			auto Keycode = button.GetKeyCode();
			if (Keycode == Unity::KeyCode::Invalid) continue;

			Keys[Keycode] = button;
		}
	}

	static void UpdateButtons(VMMDLL_SCATTER_HANDLE handle)
	{
		for (auto& [keycode, button] : Keys)
		{
			button.UpdateIsDown(handle);
		}
	}

	static Button GetButton(Unity::KeyCode keycode)
	{
		return Keys[keycode];
	}
};

inline std::unordered_map<Unity::KeyCode, Input::Button> Input::Keys;
