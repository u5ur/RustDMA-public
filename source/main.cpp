#include <Memory.h>
#include "core/core.h"

int main()
{
	if (!mem.Init("RustClient.exe", "GameAssembly.dll"))
	{
		system("pause");
		return 0;
	}

	if (FAILED(Render::InitDirectX()))
	{
		printf("Failed to init Direct X!\n");
		system("pause");
		return 0;
	}
	
	Input::SetupButtons();
	std::thread(UpdateLoop).detach();
	Render::RenderLoop(RenderPlayers);

	system("pause");
	return 0;
}
