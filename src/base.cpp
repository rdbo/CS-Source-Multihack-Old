#include <pch.h>
#include <base.h>

//Data
HMODULE            Base::Data::hModule    = (HMODULE)NULL;
void*              Base::Data::pDeviceTable[D3DDEV9_LEN];
LPDIRECT3DDEVICE9  Base::Data::pDxDevice9 = (LPDIRECT3DDEVICE9)NULL;
HWND               Base::Data::hWindow    = (HWND)NULL;
mem::voidptr_t     Base::Data::pEndScene  = (mem::voidptr_t)NULL;
EndScene_t         Base::Data::oEndScene  = (EndScene_t)NULL;
WndProc_t          Base::Data::oWndProc   = (WndProc_t)NULL;
#if defined(MEM_86)
mem::size_t        Base::Data::szEndScene = 7;
#elif defined(MEM_64)
mem::size_t        Base::Data::szEndScene = 15;
#endif
UINT               Base::Data::WmKeys[0xFF];
bool               Base::Data::Detached   = false;
bool               Base::Data::ToDetach   = false;
bool               Base::Data::ShowMenu   = true;
bool               Base::Data::InitImGui  = false;

RECT               Base::Data::WndRect   = {};
int                Base::Data::WndWidth  = 0;
int                Base::Data::WndHeight = 0;
mem::module_t      Base::Data::m_client;
mem::module_t      Base::Data::m_engine;
SDK::CSPlayer*     Base::Data::LocalPlayer;
SDK::ViewMatrix    Base::Data::vMatrix;
SDK::CSEntityList* Base::Data::EntityList;
int32_t*           Base::Data::ForceJump;

UINT               Base::Data::Keys::Bhop = VK_SPACE;

bool               Base::Data::Settings::EnableBunnyhop  = false;
bool               Base::Data::Settings::EnableSnaplines = false;
int                Base::Data::Settings::SnaplineThickness  = 1;
flColor4           Base::Data::Settings::SnaplineColorTeam  = { 0, 1, 0.5, 1 };
flColor4           Base::Data::Settings::SnaplineColorEnemy = { 1, 0.5, 0, 1 }; 
bool               Base::Data::Settings::EnableRCS = false;

//Functions

bool Base::Init()
{
	Data::m_client = mem::in::get_module("client.dll");
	Data::m_engine = mem::in::get_module("engine.dll");
	Hooks::Init();
	return true;
}

bool Base::Shutdown()
{
	Hooks::Shutdown();
	return true;
}

bool Base::Detach()
{
	Base::Shutdown();
	CreateThread(nullptr, 0, ExitThread, Data::hModule, 0, nullptr);
	return true;
}