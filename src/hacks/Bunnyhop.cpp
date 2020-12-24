#include <pch.h>
#include <base.h>

void Base::Hacks::Bunnyhop()
{
	if (Data::Settings::EnableBunnyhop && Data::WmKeys[Data::Keys::Bhop] == WM_KEYDOWN && (Data::Client->LocalPlayer->iFlags & (1 << 0)))
		*Data::Client->ForceJump = 6;
}