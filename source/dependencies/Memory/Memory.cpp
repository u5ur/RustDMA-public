#include "Memory.h"

Memory::Memory()
{
	VMM = LoadLibraryA("vmm.dll");
	FTD3XX = LoadLibraryA("FTD3XX.dll");
	LEECHCORE = LoadLibraryA("leechcore.dll");

	if (!LEECHCORE)
	{
		printf("Failed to load leechcore.dll!\n");
	}

	if (!FTD3XX)
	{
		printf("Failed to load FTD3XX.dll!\n");
	}

	if (!VMM)
	{
		printf("Failed to load VMM.dll!\n");
	}
}

Memory::~Memory()
{
	VMMDLL_CloseAll();
}

bool Memory::SetFPGA() const
{
	ULONG64 id = 0, verMajor = 0, verMinor = 0;

	if (!VMMDLL_ConfigGet(this->Handle, LC_OPT_FPGA_FPGA_ID, &id) &&
		VMMDLL_ConfigGet(this->Handle, LC_OPT_FPGA_VERSION_MAJOR, &verMajor) &&
		VMMDLL_ConfigGet(this->Handle, LC_OPT_FPGA_VERSION_MINOR, &verMinor))
	{
		return false;
	}

	if (verMajor >= 4 && (verMajor > 4 || verMinor >= 7))
	{
		LC_CONFIG cfg{ .dwVersion = LC_CONFIG_VERSION, .szDevice = "existing" };
		HANDLE h = LcCreate(&cfg);
		if (!h)
		{
			return false;
		}

		static unsigned char abort2[4] = { 0x10, 0x00, 0x10, 0x00 };
		LcCommand(h, LC_CMD_FPGA_CFGREGPCIE_MARKWR | 0x002, 4, abort2, nullptr, nullptr);
		LcClose(h);
	}

	return true;
}

bool Memory::Init(std::string process_name, std::string module_name)
{
	LPCSTR argv[] = { "", "-device", "fpga://algo=0" };

	this->Handle = VMMDLL_Initialize(3, argv);
	if (!this->Handle)
	{
		printf("Failed to initialize VMM!\n");
		return false;
	}

	if (!this->SetFPGA())
	{
		printf("Failed to set FPGA!\n");
		return false;
	}

	this->Pid = GetPidFromName(process_name);
	if (!this->Pid)
	{
		printf("Failed to find process!\n");
		return false;
	}

	if (!module_name.empty())
	{
		this->BaseAddress = GetBaseAddress(module_name);
	}
	else
	{
		this->BaseAddress = GetBaseAddress(process_name);
	}

	if (!this->BaseAddress)
	{
		printf("Failed to get base address!\n");
		return false;
	}
}

DWORD Memory::GetPidFromName(std::string process_name)
{
	DWORD pid = 0;
	VMMDLL_PidGetFromName(this->Handle, (LPSTR)process_name.c_str(), &pid);
	return pid;
}

size_t Memory::GetBaseAddress(std::string module_name)
{
	std::wstring str(module_name.begin(), module_name.end());

	PVMMDLL_MAP_MODULEENTRY module_info;
	if (!VMMDLL_Map_GetModuleFromNameW(this->Handle, this->Pid, const_cast<LPWSTR>(str.c_str()), &module_info, VMMDLL_MODULE_FLAG_NORMAL))
	{
		return 0;
	}

	return module_info->vaBase;
}

bool Memory::Read(uintptr_t address, void* buffer, size_t size) const
{
	DWORD read_size = 0;
	if (!VMMDLL_MemReadEx(this->Handle, this->Pid, address, static_cast<PBYTE>(buffer), size, &read_size, VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_ZEROPAD_ON_FAIL))
	{
		return false;
	}

	return (read_size == size);
}

VMMDLL_SCATTER_HANDLE Memory::CreateScatterHandle() const
{
	return VMMDLL_Scatter_Initialize(this->Handle, this->Pid, VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_ZEROPAD_ON_FAIL);
}

void Memory::CloseScatterHandle(VMMDLL_SCATTER_HANDLE handle)
{
	VMMDLL_Scatter_CloseHandle(handle);
}

void Memory::AddScatterRead(VMMDLL_SCATTER_HANDLE handle, uint64_t address, void* buffer, size_t size)
{
	VMMDLL_Scatter_PrepareEx(handle, address, size, static_cast<PBYTE>(buffer), NULL);
}

void Memory::ExecuteScatterRead(VMMDLL_SCATTER_HANDLE handle)
{
	VMMDLL_Scatter_ExecuteRead(handle);
	VMMDLL_Scatter_Clear(handle, this->Pid, VMMDLL_FLAG_NOCACHE | VMMDLL_FLAG_ZEROPAD_ON_FAIL);
}