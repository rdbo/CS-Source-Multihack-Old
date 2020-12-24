#include <pch.h>
#include <base.h>

void Base::Hacks::ESP_Snaplines(SDK::CSPlayer* ent, SDK::iVec2 EntPos2D)
{
	if (Data::Settings::EnableEspSnaplines)
	{
		ImVec2 screenCoords = { (float)(Data::WndWidth / 2), (float)Data::WndHeight };
		ImColor color;

		if (ent->iTeamNum == Data::Client->LocalPlayer->iTeamNum)
		{
			color = ImColor(
				Data::Settings::SnaplineColorTeam.r,
				Data::Settings::SnaplineColorTeam.g,
				Data::Settings::SnaplineColorTeam.b,
				Data::Settings::SnaplineColorTeam.a
			);
		}

		else
		{
			color = ImColor(
				Data::Settings::SnaplineColorEnemy.r,
				Data::Settings::SnaplineColorEnemy.g,
				Data::Settings::SnaplineColorEnemy.b,
				Data::Settings::SnaplineColorEnemy.a
			);
		}

		ImDrawList* Draw = ImGui::GetBackgroundDrawList();
		Draw->AddLine(screenCoords, { (float)EntPos2D.x, (float)EntPos2D.y }, color, (float)Data::Settings::SnaplineThickness);
	}
}