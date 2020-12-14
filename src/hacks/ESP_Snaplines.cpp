#include <pch.h>
#include <base.h>

void Base::Hacks::ESP_Snaplines(SDK::CSPlayer* ent, iVec2 Ent2DPos, LPDIRECT3DDEVICE9 pDevice, int wndWidth, int wndHeight)
{
	if (Data::Settings::EnableSnaplines)
	{
		iVec2 screenCoords = { wndWidth / 2, wndHeight };
		D3DCOLOR color;

		if (ent->Team == Data::LocalPlayer->Team)
		{
			color = D3DCOLOR_RGBA(
				(int)(Data::Settings::SnaplineColorTeam.r * 255),
				(int)(Data::Settings::SnaplineColorTeam.g * 255),
				(int)(Data::Settings::SnaplineColorTeam.b * 255),
				(int)(Data::Settings::SnaplineColorTeam.a * 255)
			);
		}

		else
		{
			color = D3DCOLOR_RGBA(
				(int)(Data::Settings::SnaplineColorEnemy.r * 255),
				(int)(Data::Settings::SnaplineColorEnemy.g * 255),
				(int)(Data::Settings::SnaplineColorEnemy.b * 255),
				(int)(Data::Settings::SnaplineColorEnemy.a * 255)
			);
		}


		Draw::Line(screenCoords, Ent2DPos, Data::Settings::SnaplineThickness, color, pDevice);
	}
}