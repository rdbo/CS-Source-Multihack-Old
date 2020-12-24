#include <pch.h>
#include <base.h>

void Base::Hacks::Run()
{
	Data::Client->Update();
	Data::Engine->Update();
	Data::VGuiMatSurface->Update();

	if (!Data::Client->LocalPlayer) return;

	Hacks::Bunnyhop();
}