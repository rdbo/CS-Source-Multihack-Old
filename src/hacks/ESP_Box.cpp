#include <pch.h>
#include <base.h>

void Base::Hacks::ESP_Box(SDK::CSPlayer* ent, SDK::iVec2 EntPos2D, SDK::iVec2 EntHeadPos2D)
{
	if (Data::Settings::EnableEspBox)
	{
		ImDrawList* Draw = ImGui::GetBackgroundDrawList();
		float height = (EntHeadPos2D.y - EntPos2D.y);
		ImVec2 TopLeft = { (float)EntHeadPos2D.x - (height / 4), (float)EntHeadPos2D.y };
		ImVec2 BottomRight = { (float)EntPos2D.x + (height / 4), (float)EntPos2D.y };

		ImColor color;
		ImColor filled_color;

		if (ent->iTeamNum == Data::Client->LocalPlayer->iTeamNum)
		{
			color = ImColor(
				(float)Data::Settings::BoxColorTeam.r,
				(float)Data::Settings::BoxColorTeam.g,
				(float)Data::Settings::BoxColorTeam.b,
				(float)Data::Settings::BoxColorTeam.a
			);

			filled_color = ImColor(
				(float)Data::Settings::BoxFillColorTeam.r,
				(float)Data::Settings::BoxFillColorTeam.g,
				(float)Data::Settings::BoxFillColorTeam.b,
				(float)Data::Settings::BoxFillColorTeam.a
			);
		}

		else
		{
			color = ImColor(
				(float)Data::Settings::BoxColorEnemy.r,
				(float)Data::Settings::BoxColorEnemy.g,
				(float)Data::Settings::BoxColorEnemy.b,
				(float)Data::Settings::BoxColorEnemy.a
			);

			filled_color = ImColor(
				(float)Data::Settings::BoxFillColorEnemy.r,
				(float)Data::Settings::BoxFillColorEnemy.g,
				(float)Data::Settings::BoxFillColorEnemy.b,
				(float)Data::Settings::BoxFillColorEnemy.a
			);
		}

		Draw->AddRectFilled(TopLeft, BottomRight, filled_color);
		Draw->AddRect(TopLeft, BottomRight, color, 0, 15, Data::Settings::BoxThickness);
	}
}