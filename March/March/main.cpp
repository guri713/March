#include <Windows.h>
#include <memory>
#include <cassert>
#include <tchar.h>
#include <thread>
#include <cstdio>
#include <string>


#include "system.h"
#include "ImGui/imgui_info.h"

int WINAPI wWinMain(HINSTANCE _instance, HINSTANCE _prev_instance, LPWSTR _cmd_line, INT _cmd_show)
{
	System* _system = System::GetInstance();
	_system->Startup(_instance);

	while (_system->Run())
	{
		ImGuiManager::GetInstance()->Render();
	}

	_system->Closing();

	return 0;
}