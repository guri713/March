#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <cassert>


class Window;
class DirectX11;

class System
{

	Window* window = nullptr;
	DirectX11* directX11 = nullptr;
private:
	System() {}
	~System() {}

public:
	static System* GetInstance()
	{
		static System instance;
		return &instance;
	}

	void Startup(HINSTANCE _instance,INT _cmd_show);

	bool Run();

	void Closing();
};