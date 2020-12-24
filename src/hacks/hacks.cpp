#include <pch.h>
#include <base.h>

void Base::Hacks::Run()
{
	Data::Client->Update();
	Data::Engine->Update();
	Data::VGuiMatSurface->Update();

	if (!Data::Client->LocalPlayer) return;

	Hacks::Bunnyhop();

	for (size_t i = 0; i < MAX_ENTITIES; i++, Data::Client->EntityList = (SDK::CSEntityList*)(&((mem::byte_t*)Data::Client->EntityList)[SDK::Offsets::dwDist]))
	{
		if (!(
			Data::Client->EntityList->Current &&
			Data::Client->EntityList->Current != Data::Client->LocalPlayer &&
			!Data::Client->EntityList->Current->bDormant &&
			Data::Client->EntityList->Current->iHealth > 0 &&
			Data::Client->EntityList->Current->iTeamNum != 0 &&
			Data::Client->EntityList->Current->iState == STATE_IS_ALIVE
		)) continue;

		SDK::iVec2 EntPos2D = {};
		if (SDK::WorldToScreen(Data::pDxDevice9, Data::Engine->ViewMatrix, &Data::Client->EntityList->Current->flPos, &EntPos2D))
		{
			Hacks::ESP_Snaplines(Data::Client->EntityList->Current, EntPos2D);
		}
	}
}