#include <pch.h>
#include <base.h>

void Base::Hacks::Bunnyhop()
{
	if (Data::Settings::EnableBunnyhop && Data::WmKeys[Data::Keys::Bhop] == WM_KEYDOWN && Data::LocalPlayer->Health > 0 && Data::LocalPlayer->Flags & (1 << 0))
	{
		*Data::ForceJump = 6;
	}
}