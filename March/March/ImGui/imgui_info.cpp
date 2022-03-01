#include "imgui_info.h"


void ImGuiManager::Init(HWND _handle, ID3D11Device* _device, ID3D11DeviceContext* _context, float* _screen_size)
{
#ifdef USE_IMGUI
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(_handle);
	ImGui_ImplDX11_Init(_device, _context);

	ImDrawData drawdata;
	ImGui_ImplDX11_RenderDrawData(&drawdata);
	drawdata.DisplaySize = { _screen_size[0],_screen_size[1] };

	ImGuiIO& io = ImGui::GetIO();
	// キーボードでのUI操作を可能にします。
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	// CTRL+マウスホイールでウィンドウ全体を拡大縮小できるようになります。
	io.FontAllowUserScaling = true;
	// ゲームパッドで上記のようなUI操作が可能になります。
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	io.DisplaySize = { _screen_size[0],_screen_size[1] };

	ImGui::StyleColorsDark();

#endif
}

void ImGuiManager::Update()
{
	if (is_reset)
	{
		is_reset = false;
	}
#ifdef USE_IMGUI
	//マイフレーム毎のImGuiのクリーン関数
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
#endif
}

void ImGuiManager::Render()
{
	if (is_reset)return;
#ifdef USE_IMGUI
	ImGui::Render();
#endif
}

void ImGuiManager::Uninit()
{
#ifdef USE_IMGUI
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif
}

void ImGuiManager::Reset(HWND _handle, ID3D11Device* _device, ID3D11DeviceContext* _context, float* _screen_size)
{
	is_reset = true;
	Uninit();
	Init(_handle, _device, _context, _screen_size);
}

void ImGuiManager::SetFont(const char* _font_name, const float _font_size,const float _scale)
{
	ImGuiIO& io = ImGui::GetIO();
	const char* filename = "./Data/fonts/mplus-1p-medium.ttf"; // 日本語のフォント

	// .ttfの文字の中からGetGlyphRangesJapaneseで指定された漢字などの文字をimguiの中で使えるようにします。
	ImFont* font = io.Fonts->AddFontFromFileTTF(_font_name, _font_size, NULL, io.Fonts->GetGlyphRangesJapanese());
	IM_ASSERT(font != NULL);

	// フォントの大きさを一括で変更
	io.FontGlobalScale = _scale;
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(_scale);

}
