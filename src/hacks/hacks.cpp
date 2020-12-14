#include <pch.h>
#include <base.h>

void Base::Hack()
{
	Data::LocalPlayer = *(SDK::CSPlayer**)((mem::uintptr_t)Data::m_client.base + SDK::Offsets::pLocalPlayer);
	Data::ForceJump   = (int32_t*)((mem::uintptr_t)Data::m_client.base + SDK::Offsets::dwForceJump);
	if (Data::LocalPlayer)
	{
		Hacks::Bunnyhop();
	}
}