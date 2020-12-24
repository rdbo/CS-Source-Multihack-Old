#pragma once
#ifndef BASE_H
#define BASE_H

#if defined(MEM_86)
#define WNDPROC_INDEX GWL_WNDPROC
#elif defined(MEM_64)
#define WNDPROC_INDEX GWLP_WNDPROC
#endif

#define D3DDEV9_LEN 119

#include "pch.h"
#define MAX_ENTITIES 64
#define STATE_IS_ALIVE 2

typedef HRESULT(__stdcall* EndScene_t)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK*  WndProc_t) (HWND, UINT, WPARAM, LPARAM);

DWORD WINAPI MainThread(LPVOID lpThreadParameter);
DWORD WINAPI ExitThread(LPVOID lpThreadParameter);

namespace Base
{
	bool Init();
	bool Shutdown();
	bool Detach();

	namespace Data
	{
		extern HMODULE           hModule;
		extern LPDIRECT3DDEVICE9 pDxDevice9;
		extern void*             pDeviceTable[D3DDEV9_LEN];
		extern HWND              hWindow;
		extern mem::voidptr_t    pEndScene;
		extern EndScene_t        oEndScene;
		extern WndProc_t         oWndProc;
		extern mem::size_t       szEndScene;
		extern UINT              WmKeys[0xFF];
		extern bool              Detached;
		extern bool              ToDetach;
		extern bool              InitImGui;
		extern bool              ShowMenu;

		extern int  WndWidth;
		extern int  WndHeight;
		extern RECT WndRect;
		extern SDK::CSClient*         Client;
		extern SDK::CSEngine*         Engine;
		extern SDK::CSVGUIMatSurface* VGuiMatSurface;

		namespace Settings
		{
			extern bool EnableBunnyhop;
			extern bool EnableEspSnaplines;
			extern SDK::flColor4 SnaplineColorTeam;
			extern SDK::flColor4 SnaplineColorEnemy;
			extern int           SnaplineThickness;
		}

		namespace Keys
		{
			const  UINT ToggleMenu = VK_INSERT;
			const  UINT DetachDll  = VK_END;
			extern UINT Bhop;
		}
	}

	namespace Hacks
	{
		void Run();
		void Bunnyhop();
		void ESP_Snaplines(SDK::CSPlayer* ent, SDK::iVec2 EntPos2D);
	}

	namespace Hooks
	{
		bool Init();
		bool Shutdown();
		HRESULT __stdcall EndScene(LPDIRECT3DDEVICE9 pDevice);
		LRESULT CALLBACK  WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	}
}

#endif