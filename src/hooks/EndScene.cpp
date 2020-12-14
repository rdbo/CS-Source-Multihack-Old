#include <pch.h>
#include <base.h>

HRESULT __stdcall Base::Hooks::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	Data::pDxDevice9 = pDevice;
	GetWindowRect(Data::hWindow, &Data::WndRect);
	Data::WndWidth  = Data::WndRect.right  - Data::WndRect.left;
	Data::WndHeight = Data::WndRect.bottom - Data::WndRect.top;

	if (!Data::InitImGui)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImGui_ImplWin32_Init(Data::hWindow);
		ImGui_ImplDX9_Init(pDevice);
		Data::InitImGui = true;
	}

	if (!Data::InitImGui) return Data::oEndScene(pDevice);

	Base::Hack();

	/*
	Draw::Line({ 10, 10 }, { 20, 10 }, 2, D3DCOLOR_RGBA(255, 0, 0, 255), pDevice);
	Draw::Rectangle(10, 20, 50, 50, 4, D3DCOLOR_RGBA(125, 125, 0, 255), pDevice);
	Draw::FilledRectangle(10, 30, 50, 50, D3DCOLOR_RGBA(0, 255, 0, 255), pDevice);
	*/

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (Data::ShowMenu)
	{
		ImGui::Begin("CS-Source Multihack by rdbo");
		ImGui::Checkbox("Bunnyhop", &Data::Settings::EnableBunnyhop);
		ImGui::Checkbox("ESP Snaplines", &Data::Settings::EnableSnaplines);
		ImGui::ColorEdit4("Snapline Team", reinterpret_cast<float(&)[4]>(Data::Settings::SnaplineColorTeam));
		ImGui::ColorEdit4("Snapline Enemy", reinterpret_cast<float(&)[4]>(Data::Settings::SnaplineColorEnemy));
		if (ImGui::Button("Detach"))
		{
			ImGui::End();
			ImGui::EndFrame();
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			Base::Detach();
			return Data::oEndScene(pDevice);
		}
		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return Data::oEndScene(pDevice);
}