#include "baseScene.h"
#include "sceneManager.h"
#include "../ImGui/imgui_info.h"

SceneManager::SceneManager()
{
	next_scene = nullptr;
	is_stack = false;
	delete_stack = false;
	scene_array.clear();
}

void SceneManager::Init(BaseScene* _first_scene)
{
	if (!scene_array.empty())
	{
		scene_array.clear();
	}
	scene_array.push_back(_first_scene);
	scene_array.back()->Init();
	next_scene = nullptr;
	delete_stack = false;
}

void SceneManager::Update()
{
	if (next_scene)
		ChangeScene();
	if (delete_stack)
		DeleteStackScene();
	//アクティブシーンのみ更新
	for (auto& _scene : scene_array)
	{
		if (_scene->GetIsStack())
			continue;
		//cameraManager::GetInstance()->Update();
		//ImGuiUpdate();
#ifdef USE_IMGUI
		_scene->ImGui();
#endif
		_scene->Update();
	}

}

void SceneManager::Render()
{
	for (auto& _scene : scene_array)
	{
		if (_scene->GetEnableRender())
			_scene->Render();
	}

	ImGuiManager::GetInstance()->Render();
}

void SceneManager::Uninit()
{
	for (auto& _scene : scene_array)
		delete _scene;

	scene_array.clear();
}

void SceneManager::ChangeScene()
{
	if (!is_stack)//シーンをスタックしない時は今保持しているシーンをすべて削除する
	{
		if (!scene_array.empty())
		{
			for (auto& _scene : scene_array)
				delete _scene;
			scene_array.clear();
		}
	}
	else//シーンをスタックするとき
	{
		//今から作るシーン以外をスタック状態にする
		if (!scene_array.empty())
		{
			for (auto& _scene : scene_array)
			{
				_scene->SetIsStack(true);
			}
		}
	}
	scene_array.push_back(next_scene);

	scene_array.back()->Init();
	next_scene = nullptr;
}

void SceneManager::DeleteStackScene()
{
	scene_array.erase(scene_array.begin() + 1, scene_array.end());
}

const wchar_t* SceneManager::GetActiveSceneName()
{
	for (auto& _scene : scene_array)
	{
		if (_scene->GetIsStack())
			continue;
		return _scene->GetName();
	}
	assert(0 && "no active scene");
	return L"no_name";
}

