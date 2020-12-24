#pragma once
#ifndef SDK_H
#define SDK_H

#include <iostream>
#include <cstdint>
#include <libmem++/libmem.hpp>

#define SDK_OFFSET(offset) (&((char*)this->Module.base)[offset])
#define SDK_UNION_VAR(type, varname, offset) CREATE_UNION_MEMBER(type, varname, offset)

namespace SDK
{
	namespace Offsets
	{
		//client.dll
		const uintptr_t dwForceJump  = 0x4F3B3C;
		const uintptr_t pLocalPlayer = 0x4C6708;
		const uintptr_t pEntityList  = 0x4D3904;
		const uintptr_t fnGameInput  = 0x1489C7;

		//engine.dll
		const uintptr_t bHookCursor = 0x3C00C4;
		const uintptr_t flViewMatrix = 0x5ADBF8;

		//vguimatsurface.dll
		const uintptr_t bShowCursor = 0x135008;

		//CSPlayer
		const uintptr_t dwHealth = 0x94;
		const uintptr_t dwTeamNum = 0x9C;
		const uintptr_t dwState = 0x178;
		const uintptr_t bDormant = 0x17E;
		const uintptr_t flPos = 0x260;
		const uintptr_t dwFlags = 0x350;


		//CSEntityList
		const uintptr_t dwDist = 0x10;
	}

	struct iVec2
	{
		int x, y;
	};

	struct iVec3
	{
		int x, y, z;
	};

	struct iVec4
	{
		int x, y, z, w;
	};

	struct flVec2
	{
		float x, y;
	};

	struct flVec3
	{
		float x, y, z;
	};

	struct flVec4
	{
		float x, y, z, w;
	};

	struct iColor3
	{
		int r, g, b;
	};

	struct iColor4
	{
		int r, g, b, a;
	};

	struct flColor3
	{
		float r, g, b;
	};

	struct flColor4
	{
		float r, g, b, a;
	};

	typedef bool bool_t;
	typedef char byte_t;

	class CSPlayer
	{
	public:
		union
		{
			SDK_UNION_VAR(int32_t, iHealth,  Offsets::dwHealth);
			SDK_UNION_VAR(int32_t, iTeamNum, Offsets::dwTeamNum);
			SDK_UNION_VAR(int32_t, iState,   Offsets::dwState);
			SDK_UNION_VAR(bool_t,  bDormant, Offsets::bDormant);
			SDK_UNION_VAR(flVec3,  flPos,    Offsets::flPos);
			SDK_UNION_VAR(int32_t, iFlags,   Offsets::dwFlags);
		};
	};

	struct CSEntityList
	{
		CSPlayer* Current;
	};

	struct ViewMatrix_t
	{
		float Matrix[4][4];
	};

	class GameModule
	{
	public:
		bool IsValid = false;
		mem::module_t Module;
	protected:
		bool Setup(std::string module_name)
		{
			this->Module = mem::in::get_module(module_name);
			return this->Module.is_valid();
		}

		void Update()
		{

		}
	};

	class CSClient : public GameModule
	{
	public:
		uint32_t* ForceJump = (uint32_t*)NULL;
		CSPlayer* LocalPlayer = (CSPlayer*)NULL;
		CSEntityList* EntityList = (CSEntityList*)NULL;

	public:
		CSClient()
		{
			if (!this->Setup("client.dll"))
				return;

			this->Update();

			this->IsValid = true;
		}

		void Update()
		{
			this->ForceJump = (uint32_t*)SDK_OFFSET(Offsets::dwForceJump);
			this->LocalPlayer = *(CSPlayer**)SDK_OFFSET(Offsets::pLocalPlayer);
			this->EntityList = (CSEntityList*)SDK_OFFSET(Offsets::pEntityList);
		}
	};

	class CSEngine : public GameModule
	{
	public:
		bool_t* HookCursor = (bool_t*)NULL;
		ViewMatrix_t* ViewMatrix = (ViewMatrix_t*)NULL;

	public:
		CSEngine()
		{
			if (!this->Setup("engine.dll"))
				return;

			this->Update();

			this->IsValid = true;
		}

		void Update()
		{
			this->HookCursor = (bool_t*)SDK_OFFSET(Offsets::bHookCursor);
			this->ViewMatrix = (ViewMatrix_t*)SDK_OFFSET(Offsets::flViewMatrix);
		}
	};

	class CSVGUIMatSurface : public GameModule
	{
	public:
		bool_t* ShowCursor = (bool_t*)NULL;
	public:
		CSVGUIMatSurface()
		{
			if (!this->Setup("vguimatsurface.dll"))
				return;

			this->Update();

			this->IsValid = true;
		}

		void Update()
		{
			this->ShowCursor = (bool_t*)SDK_OFFSET(Offsets::bShowCursor);
		}
	};

	inline bool WorldToScreen(LPDIRECT3DDEVICE9 pDevice, ViewMatrix_t* vmatrix, flVec3* pos, iVec2* out)
	{
		D3DXVECTOR2 screenVec;
		screenVec.x = pos->x * vmatrix->Matrix[0][0] + pos->y * vmatrix->Matrix[0][1] + pos->z * vmatrix->Matrix[0][2] + vmatrix->Matrix[0][3];
		screenVec.y = pos->x * vmatrix->Matrix[1][0] + pos->y * vmatrix->Matrix[1][1] + pos->z * vmatrix->Matrix[1][2] + vmatrix->Matrix[1][3];

		const auto w = pos->x * vmatrix->Matrix[3][0] + pos->y * vmatrix->Matrix[3][1] + pos->z * vmatrix->Matrix[3][2] + vmatrix->Matrix[3][3];
		if (w < 0.1f)
			return false;

		screenVec.x /= w;
		screenVec.y /= w;

		D3DVIEWPORT9 viewPort;
		pDevice->GetViewport(&viewPort);

		out->x = (int)((viewPort.Width / 2) + ((screenVec.x / 2) * viewPort.Width + 0.5f));
		out->y = (int)((viewPort.Height / 2) - ((screenVec.y / 2) * viewPort.Height + 0.5f));

		return true;
	}
}

#endif