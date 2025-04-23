#pragma once

struct String
{
	char pad[0x10]{};
	int size = 0;
	wchar_t str[129]{};

	String() = default;

	String(uint64_t addr)
	{
		if (!addr) return;
		mem.Read(addr, this, sizeof(String));
		str[std::min(size, 128)] = L'\0';
	}
};
