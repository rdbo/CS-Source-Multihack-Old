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

		ImGuiStyle& style = ImGui::GetStyle();

		style.WindowRounding = 0.f;
		style.TabRounding    = 0.f;
		style.TabRounding    = 0.f;

		style.Colors[ImGuiCol_Text]                  = ImColor(1.f, 1.f, 1.f, 1.f);
		style.Colors[ImGuiCol_TextDisabled]          = ImColor(0.8f, 0.8f, 0.8f, 1.f);
		style.Colors[ImGuiCol_WindowBg]              = ImColor(0.025f, 0.025f, 0.025f, 1.f);
		style.Colors[ImGuiCol_ChildBg]               = style.Colors[ImGuiCol_WindowBg];
		style.Colors[ImGuiCol_PopupBg]               = style.Colors[ImGuiCol_WindowBg];
		style.Colors[ImGuiCol_Border]                = ImColor(0.8f, 0.f, 0.f, 1.f);
		style.Colors[ImGuiCol_BorderShadow]          = ImColor(0.f, 0.f, 0.f, 0.f);
		style.Colors[ImGuiCol_FrameBg]               = ImColor(0.1f, 0.1f, 0.1f, 1.f);
		style.Colors[ImGuiCol_FrameBgHovered]        = ImColor(0.175f, 0.175f, 0.175f, 1.f);
		style.Colors[ImGuiCol_FrameBgActive]         = ImColor(0.25f, 0.25f, 0.25f, 1.f);
		style.Colors[ImGuiCol_TitleBg]               = ImColor(0.7f, 0.f, 0.f, 1.f);
		style.Colors[ImGuiCol_TitleBgActive]         = ImColor(0.9f, 0.f, 0.f, 1.f);
		style.Colors[ImGuiCol_TitleBgCollapsed]      = ImColor(0.9f, 0.f, 0.f, 0.5f);
		style.Colors[ImGuiCol_MenuBarBg]             = ImColor(0.f, 0.f, 0.f, 1.f);
		style.Colors[ImGuiCol_ScrollbarBg]           = ImColor(0.1f, 0.1f, 0.1f, 1.f);
		style.Colors[ImGuiCol_ScrollbarGrab]         = ImColor(0.5f, 0.5f, 0.5f, 1.f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImColor(0.7f, 0.7f, 0.7f, 1.f);
		style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImColor(0.9f, 0.9f, 0.9f, 1.f);
		style.Colors[ImGuiCol_CheckMark]             = ImColor(1.f,  0.f,  0.f,  1.f);
		style.Colors[ImGuiCol_SliderGrab]            = style.Colors[ImGuiCol_ScrollbarGrab];
		style.Colors[ImGuiCol_SliderGrabActive]      = style.Colors[ImGuiCol_ScrollbarGrabActive];
		style.Colors[ImGuiCol_Button]                = style.Colors[ImGuiCol_FrameBg];
		style.Colors[ImGuiCol_ButtonHovered]         = style.Colors[ImGuiCol_FrameBgHovered];
		style.Colors[ImGuiCol_ButtonActive]          = style.Colors[ImGuiCol_FrameBgActive];
		style.Colors[ImGuiCol_Header]                = style.Colors[ImGuiCol_FrameBg];
		style.Colors[ImGuiCol_HeaderHovered]         = style.Colors[ImGuiCol_FrameBgHovered];
		style.Colors[ImGuiCol_HeaderActive]          = style.Colors[ImGuiCol_FrameBgActive];
		style.Colors[ImGuiCol_Separator]             = ImColor();
		style.Colors[ImGuiCol_SeparatorHovered]      = ImColor();
		style.Colors[ImGuiCol_SeparatorActive]       = ImColor();
		style.Colors[ImGuiCol_ResizeGrip]            = ImColor();
		style.Colors[ImGuiCol_ResizeGripHovered]     = ImColor();
		style.Colors[ImGuiCol_ResizeGripActive]      = ImColor();
		style.Colors[ImGuiCol_Tab]                   = ImColor(0.2f, 0.2f, 0.2f, 0.2f);
		style.Colors[ImGuiCol_TabHovered]            = ImColor(0.7f, 0.f, 0.f, 1.f);
		style.Colors[ImGuiCol_TabActive]             = ImColor(1.f, 0.f, 0.f, 1.f);
		style.Colors[ImGuiCol_TabUnfocused]          = ImColor();
		style.Colors[ImGuiCol_TabUnfocusedActive]    = ImColor();
		style.Colors[ImGuiCol_PlotLines]             = ImColor();
		style.Colors[ImGuiCol_PlotLinesHovered]      = ImColor();
		style.Colors[ImGuiCol_PlotHistogram]         = ImColor();
		style.Colors[ImGuiCol_PlotHistogramHovered]  = ImColor();
		style.Colors[ImGuiCol_TableHeaderBg]         = ImColor();
		style.Colors[ImGuiCol_TableBorderStrong]     = ImColor();
		style.Colors[ImGuiCol_TableBorderLight]      = ImColor();
		style.Colors[ImGuiCol_TableRowBg]            = ImColor();
		style.Colors[ImGuiCol_TableRowBgAlt]         = ImColor();
		style.Colors[ImGuiCol_TextSelectedBg]        = ImColor();
		style.Colors[ImGuiCol_DragDropTarget]        = ImColor();
		style.Colors[ImGuiCol_NavHighlight]          = ImColor();
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImColor();
		style.Colors[ImGuiCol_NavWindowingDimBg]     = ImColor();
		style.Colors[ImGuiCol_ModalWindowDimBg]      = ImColor();
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

		ImGui::Begin("Counter-Strike: Source Multihack by rdbo", 0, ImGuiWindowFlags_NoTitleBar);

		/*
		//OLD MENU
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
		*/

		ImGui::BeginTabBar("navbar");
		if (ImGui::BeginTabItem("Aim"))
		{
			ImGui::Text("Nothing here :P");
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("ESP"))
		{
			ImGui::Checkbox("Enable ESP Snaplines", &Data::Settings::EnableEspSnaplines);
			if (Data::Settings::EnableEspSnaplines && ImGui::Button("Configure ESP Snaplines..."))
				Data::ShowEspSnaplinesSettings = !Data::ShowEspSnaplinesSettings;

			if (Data::Settings::EnableEspSnaplines && Data::ShowEspSnaplinesSettings)
			{
				ImGui::Begin("ESP Snaplines Settings");
				ImGui::SliderInt("Line Thickness", &Data::Settings::SnaplineThickness, 0, 50);
				ImGui::ColorEdit4("Line Color Team", reinterpret_cast<float(&)[4]>(Data::Settings::SnaplineColorTeam));
				ImGui::ColorEdit4("Line Color Enemy", reinterpret_cast<float(&)[4]>(Data::Settings::SnaplineColorEnemy));
				ImGui::End();
			}

			ImGui::Checkbox("Enable ESP Box", &Data::Settings::EnableEspBox);
			if (Data::Settings::EnableEspBox && ImGui::Button("Configure ESP Box..."))
				Data::ShowEspBoxSettings = !Data::ShowEspBoxSettings;

			if (Data::Settings::EnableEspBox && Data::ShowEspBoxSettings)
			{
				ImGui::Begin("ESP Box Settings");
				ImGui::SliderInt("Box Thickness", &Data::Settings::BoxThickness, 0, 50);
				ImGui::ColorEdit4("Box Color Team", reinterpret_cast<float(&)[4]>(Data::Settings::BoxColorTeam));
				ImGui::ColorEdit4("Box Color Enemy", reinterpret_cast<float(&)[4]>(Data::Settings::BoxColorEnemy));
				ImGui::ColorEdit4("Box Fill Team", reinterpret_cast<float(&)[4]>(Data::Settings::BoxFillColorTeam));
				ImGui::ColorEdit4("Box Fill Enemy", reinterpret_cast<float(&)[4]>(Data::Settings::BoxFillColorEnemy));
				ImGui::End();
			}

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Visuals"))
		{
			ImGui::Checkbox("No Flash", &Data::Settings::EnableNoFlash);
			if (Data::Settings::EnableNoFlash && ImGui::Button("Configure No Flash..."))
				Data::ShowNoFlashSettings = !Data::ShowNoFlashSettings;

			if (Data::Settings::EnableNoFlash && Data::ShowNoFlashSettings)
			{
				ImGui::Begin("No Flash Settings");
				ImGui::SliderFloat("Flash Duration", &Data::Settings::FlashTime, 0.f, 100.f);
				ImGui::SliderFloat("Flash Alpha", &Data::Settings::FlashAlpha, 0.f, 255.f);
				ImGui::End();
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Misc"))
		{
			ImGui::Checkbox("Bunnyhop", &Data::Settings::EnableBunnyhop);
			ImGui::Checkbox("Watermark", &Data::ShowWatermark);
			if (ImGui::Combo("Font Size", &Data::ActiveFontId, Data::FontList, 3))
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

			if (ImGui::Button("Detach"))
				Data::ToDetach = true;

			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();

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