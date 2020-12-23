#include <pch.h>
#include <base.h>

HRESULT __stdcall Base::Hooks::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	Data::pDxDevice9 = pDevice;
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

	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (Data::ShowMenu)
	{
		if (!*Data::VGuiMatSurface->ShowCursor)
		{
			io.MouseDrawCursor = true;
			//*Data::VGuiMatSurface->ShowCursor = true;
		}

		if (*Data::Engine->HookCursor)
			*Data::Engine->HookCursor = false;

		ImGui::Begin("ImGui Window");
		ImGui::Text("Test ImGUI Window");
		if (ImGui::Button("Detach"))
			Data::ToDetach = true;
		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	if (Data::ToDetach)
	{
		*Data::Engine->HookCursor = true;
		Base::Detach();
	}
	return Data::oEndScene(pDevice);
}