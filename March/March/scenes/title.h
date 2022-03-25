#pragma once
#include "../original engine/scene/baseScene.h"

class Title : public BaseScene
{
public:
	void Init();
	void Update();
	void Render();
	void Uninit();
	void ImGui();
};