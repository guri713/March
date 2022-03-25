#pragma once
#include <string>

class BaseScene
{
protected:
	bool is_stack = false;
	bool enable_render = true;
	std::wstring scene_name;

public:
	BaseScene() {}
	virtual ~BaseScene() {}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Uninit() {}
	virtual void ImGui() {}

	const bool GetIsStack() { return is_stack; }
	const bool GetEnableRender() { return enable_render; }
	const wchar_t* GetName() { return scene_name.c_str(); }
	
	void SetIsStack(const bool _flg) { is_stack = _flg; }
	void SetEnableRender(const bool _flg) { enable_render = _flg; }
};