#include <pch.h>
#include <base.h>

static float g_oFlashTime = 0;
static float g_oFlashAlpha = 0;
static bool  g_DefaultsRestored = false;

void Base::Hacks::NoFlash()
{
	if (!g_oFlashTime)
		g_oFlashTime = Data::Client->LocalPlayer->flFlashDuration;

	if (!g_oFlashAlpha)
		g_oFlashAlpha = Data::Client->LocalPlayer->flFlashMaxAlpha;

	if (Data::Settings::EnableNoFlash)
	{
		if (Data::Client->LocalPlayer->flFlashDuration != Data::Settings::FlashTime)
			Data::Client->LocalPlayer->flFlashDuration = Data::Settings::FlashTime;

		if (Data::Client->LocalPlayer->flFlashMaxAlpha != Data::Settings::FlashAlpha)
			Data::Client->LocalPlayer->flFlashMaxAlpha = Data::Settings::FlashAlpha;

		if(g_DefaultsRestored)
			g_DefaultsRestored = false;
	}

	else if(!g_DefaultsRestored)
	{
		Data::Client->LocalPlayer->flFlashDuration = g_oFlashTime;
		Data::Client->LocalPlayer->flFlashMaxAlpha = g_oFlashAlpha;
		g_DefaultsRestored = true;
	}
}