#pragma once
#include <Windows.h>
#include <string>
#include <cstdint>
#include <vmmdll.h>
#include <leechcore.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>

class Memory
{
private:

	VMM_HANDLE Handle;

	HMODULE VMM = nullptr;
	HMODULE FTD3XX = nullptr;
	HMODULE LEECHCORE = nullptr;

	bool SetFPGA() const;

public:

	uint32_t Pid;
	uint64_t BaseAddress;

	Memory();

	~Memory();

	bool Init(std::string process_name, std::string module_name = "");

	DWORD GetPidFromName(std::string process_name);

	size_t GetBaseAddress(std::string module_name);

	bool Read(uintptr_t address, void* buffer, size_t size) const;

	template <typename T>
	T Read(void* address)
	{
		T buffer{ };
		memset(&buffer, 0, sizeof(T));
		Read(reinterpret_cast<uint64_t>(address), reinterpret_cast<void*>(&buffer), sizeof(T));

		return buffer;
	}

	template <typename T>
	T Read(uint64_t address)
	{
		return Read<T>(reinterpret_cast<void*>(address));
	}

	VMMDLL_SCATTER_HANDLE CreateScatterHandle() const;

	void CloseScatterHandle(VMMDLL_SCATTER_HANDLE handle);

	void AddScatterRead(VMMDLL_SCATTER_HANDLE handle, uint64_t address, void* buffer, size_t size);

	void ExecuteScatterRead(VMMDLL_SCATTER_HANDLE handle);
};

inline Memory mem;