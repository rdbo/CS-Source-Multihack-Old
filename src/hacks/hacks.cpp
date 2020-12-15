#include <pch.h>
#include <base.h>

void Base::Hack()
{
	Data::LocalPlayer = *(SDK::CSPlayer**)((mem::uintptr_t)Data::m_client.base + SDK::Offsets::pLocalPlayer);
	Data::vMatrix     = *(SDK::ViewMatrix*)((mem::uintptr_t)Data::m_engine.base + SDK::Offsets::dwViewMatrix);
	Data::ForceJump   = (int32_t*)((mem::uintptr_t)Data::m_client.base + SDK::Offsets::dwForceJump);
	if (Data::LocalPlayer)
	{
		Hacks::Bunnyhop();
		Hacks::RCS();

		Data::EntityList = (SDK::CSEntityList*)((mem::uintptr_t)Data::m_client.base + SDK::Offsets::pEntityList);
		for (size_t i = 0; i < MAX_ENTITIES; i++, Data::EntityList = (SDK::CSEntityList*)((uintptr_t)Data::EntityList + SDK::Offsets::dwDist))
		{
			if (Data::EntityList && Data::EntityList->Entity && Data::EntityList->Entity != Data::LocalPlayer && !Data::EntityList->Entity->Dormant && Data::EntityList->Entity->State != 0 && Data::EntityList->Entity->Health > 0 && Data::EntityList->Entity->Team != 0)
			{
				iVec2 Ent2DPos = {};
				D3DXVECTOR3 pos, out;
				pos = D3DXVECTOR3(
					Data::EntityList->Entity->Position.x, 
					Data::EntityList->Entity->Position.y,
					Data::EntityList->Entity->Position.z
				);

				if (SDK::WorldToScreen(Data::pDxDevice9, Data::vMatrix, &pos, &out))
				{
					Ent2DPos = { (int)out.x, (int)out.y };
					Hacks::ESP_Snaplines(Data::EntityList->Entity, Ent2DPos, Data::pDxDevice9, Data::WndWidth, Data::WndHeight);
				}
			}
		}
	}
}