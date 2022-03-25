#include <Windows.h>
#include <memory>
#include <cassert>
#include <tchar.h>
#include <thread>
#include <cstdio>
#include <string>


#include "original engine/main system/system.h"
#include "original engine/ImGui/imgui_info.h"
#include "original engine/scene/baseScene.h"
#include "original engine/scene/sceneManager.h"
#include "scenes/title.h"

INT WINAPI wWinMain(HINSTANCE _instance, HINSTANCE _prev_instance, LPWSTR _cmd_line, INT _cmd_show)
{
	System* _system = System::GetInstance();
	_system->Startup(_instance,_cmd_show);
	SceneManager* _scene_manager = SceneManager::GetInstance();
	_scene_manager->Init(new Title());

	while (_system->Run())
	{
		_scene_manager->Update();
		_scene_manager->Render();
	}

	_system->Closing();

	return 0;
}