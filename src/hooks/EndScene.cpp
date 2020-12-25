#include <pch.h>
#include <base.h>

HRESULT __stdcall Base::Hooks::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	Data::pDxDevice9 = pDevice;
	GetClientRect(Data::hWindow, &Data::WndRect);
	Data::WndWidth  = Data::WndRect.right - Data::WndRect.left;
	Data::WndHeight = Data::WndRect.bottom - Data::WndRect.top;

	if (!Data::InitImGui)
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		ImGui_ImplWin32_Init(Data::hWindow);
		ImGui_ImplDX9_Init(pDevice);
		Data::InitImGui = true;

		ImFontConfig font_cfg = {};
		font_cfg.FontDataOwnedByAtlas = false;
		Data::UbuntuRegularSmall  = io.Fonts->AddFontFromMemoryTTF((void*)Ubuntu_Regular_ttf, sizeof(Ubuntu_Regular_ttf), 14, &font_cfg);
		Data::UbuntuRegularMedium = io.Fonts->AddFontFromMemoryTTF((void*)Ubuntu_Regular_ttf, sizeof(Ubuntu_Regular_ttf), 18, &font_cfg);
		Data::UbuntuRegularLarge  = io.Fonts->AddFontFromMemoryTTF((void*)Ubuntu_Regular_ttf, sizeof(Ubuntu_Regular_ttf), 24, &font_cfg);
		Data::ActiveFont          = Data::UbuntuRegularSmall;
	}

	if (!Data::InitImGui) return Data::oEndScene(pDevice);

	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::PushFont(Data::ActiveFont);

	Hacks::Run();

	ImDrawList* DrawBg = ImGui::GetBackgroundDrawList();
	if (Data::ShowWatermark)
		DrawBg->AddText({20, 2}, ImColor(1.f, 1.f, 1.f, 1.f), "Counter-Strike: Source Multihack by rdbo");

	if (Data::ShowMenu)
	{
		if (!*Data::VGuiMatSurface->ShowCursor)
		{
			io.MouseDrawCursor = true;
			//*Data::VGuiMatSurface->ShowCursor = true;
		}

		if (*Data::Engine->HookCursor)
			*Data::Engine->HookCursor = false;

		ImGui::Begin("Counter-Strike: Source Multihack by rdbo");
		ImGui::Checkbox("Watermark", &Data::ShowWatermark);
		if (ImGui::ListBox("Font Size", &Data::ActiveFontId, Data::FontList, 3))
		{
			switch (Data::ActiveFontId)
			{
			case 0:
				Data::ActiveFont = Data::UbuntuRegularSmall;
				break;
			case 1:
				Data::ActiveFont = Data::UbuntuRegularMedium;
				break;
			case 2:
				Data::ActiveFont = Data::UbuntuRegularLarge;
				break;
			}
		}

		ImGui::Checkbox("Bunnyhop", &Data::Settings::EnableBunnyhop);
		ImGui::Checkbox("ESP Snaplines", &Data::Settings::EnableEspSnaplines);
		ImGui::ColorEdit4("Snaplines Team", reinterpret_cast<float(&)[4]>(Data::Settings::SnaplineColorTeam));
		ImGui::ColorEdit4("Snaplines Enemy", reinterpret_cast<float(&)[4]>(Data::Settings::SnaplineColorEnemy));
		ImGui::SliderInt("Snapline Thickness", &Data::Settings::SnaplineThickness, 0, 50);
		ImGui::Checkbox("No Flash", &Data::Settings::EnableNoFlash);
		ImGui::SliderFloat("Flash Duration", &Data::Settings::FlashTime, 0.f, 100.f);
		ImGui::SliderFloat("Flash Alpha", &Data::Settings::FlashAlpha, 0.f, 255.f);
		ImGui::Checkbox("Enable ESP Box", &Data::Settings::EnableEspBox);
		ImGui::ColorEdit4("Box Team", reinterpret_cast<float(&)[4]>(Data::Settings::BoxColorTeam));
		ImGui::ColorEdit4("Box Enemy", reinterpret_cast<float(&)[4]>(Data::Settings::BoxColorEnemy));
		ImGui::ColorEdit4("Box Fill Team", reinterpret_cast<float(&)[4]>(Data::Settings::BoxFillColorTeam));
		ImGui::ColorEdit4("Box Fill Enemy", reinterpret_cast<float(&)[4]>(Data::Settings::BoxFillColorEnemy));
		ImGui::SliderInt("Box Thickness", &Data::Settings::BoxThickness, 0, 50);
		if (ImGui::Button("Detach"))
			Data::ToDetach = true;
		ImGui::End();
	}

	ImGui::PopFont();
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