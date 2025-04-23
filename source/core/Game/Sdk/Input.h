#pragma once

class Input
{
public:

	class Button
	{
	public:

		uint64_t Address = 0;

		Unity::String GetName()
		{
			if (!this->Address) return {};
			return mem.Read<Unity::String>(mem.Read<uint64_t>(this->Address + offsets::Name));
		}

		uint64_t GetBinds()
		{
			if (!this->Address) return 0;
			return mem.Read<uint64_t>(this->Address + offsets::Binds);
		}

		bool IsDown()
		{
			if (!this->Address) return false;
			return mem.Read<bool>(this->Address + offsets::IsDown);
		}

		Unity::KeyCode GetKeyCode()
		{
			if (!this->Address) return Unity::KeyCode::Invalid;
			return mem.Read<Unity::KeyCode>(this->Address + offsets::Code);
		}
	};

	static uint64_t GetButtons()
	{
		uint64_t TypeInfo = mem.Read<uint64_t>(mem.BaseAddress + offsets::FacepunchInput);
		if (!TypeInfo) return 0;

		uint64_t StaticFields = mem.Read<uint64_t>(TypeInfo + 0xB8);
		if (!StaticFields) return 0;

		return mem.Read<uint64_t>(StaticFields + offsets::Buttons);
	}
};