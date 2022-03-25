#pragma once

#include <vector>
#include <string>

class BaseScene;

class SceneManager
{
private:
	std::vector<BaseScene*> scene_array;
	BaseScene* next_scene;
	bool is_stack;
	bool delete_stack;

	SceneManager();
	~SceneManager() {}

public:
	static SceneManager* GetInstance()
	{
		static SceneManager _instance;
		return &_instance;
		
	}

	void Init(BaseScene* _first_scene);

	void Update();

	void Render();
	
	void Uninit();


	void SetNextScene(BaseScene* _next_scene, bool _is_stack, int _now_scene = 0);

	int GetSceneCount() { return scene_array.size(); }
	const wchar_t* GetActiveSceneName();

private:
	void ChangeScene();
	void DeleteStackScene();
};