#pragma once
#ifndef SDK_H
#define SDK_H

#include <iostream>
#include <cstdint>
#include <libmem++/libmem.hpp>
#include <base_types.h>
#define MAX_ENTITIES 32

namespace SDK
{
	namespace Offsets
	{
		//client.dll
		const uintptr_t pLocalPlayer = 0x4C6708;
		const uintptr_t pEntityList  = 0x4D3904;
		const uintptr_t dwForceJump  = 0x4F3B3C;

		//engine.dll
		const uintptr_t dwViewMatrix = 0x5ADBF8;

		//CSPlayer
		const uintptr_t dwHealth  = 0x94;
		const uintptr_t dwTeamNum = 0x9C;
		const uintptr_t dwState   = 0x178;
		const uintptr_t bDormant  = 0x17E;
		const uintptr_t dwPos     = 0x260;
		const uintptr_t dwFlags   = 0x350;

		//CSEntityList
		const uintptr_t dwDist = 0x10;
	}

	class CSPlayer
	{
	public:
		union
		{
			CREATE_UNION_MEMBER(int32_t, Health, Offsets::dwHealth);
			CREATE_UNION_MEMBER(int32_t, Team, Offsets::dwTeamNum);
			CREATE_UNION_MEMBER(int32_t, State, Offsets::dwState);
			CREATE_UNION_MEMBER(bool, Dormant, Offsets::bDormant);
			CREATE_UNION_MEMBER(flVec3, Position, Offsets::dwPos);
			CREATE_UNION_MEMBER(int32_t, Flags, Offsets::dwFlags);
		};
	};

	struct CSEntityList
	{
		CSPlayer* Entity;
	};

	struct ViewMatrix
	{
		float matrix[4][4];
	};

	inline bool WorldToScreen(LPDIRECT3DDEVICE9 pDevice, ViewMatrix vmatrix, D3DXVECTOR3* pos, D3DXVECTOR3* out)
	{
		D3DXVECTOR2 screenVec;
		screenVec.x = pos->x * vmatrix.matrix[0][0] + pos->y * vmatrix.matrix[0][1] + pos->z * vmatrix.matrix[0][2] + vmatrix.matrix[0][3];
		screenVec.y = pos->x * vmatrix.matrix[1][0] + pos->y * vmatrix.matrix[1][1] + pos->z * vmatrix.matrix[1][2] + vmatrix.matrix[1][3];

		const auto w = pos->x * vmatrix.matrix[3][0] + pos->y * vmatrix.matrix[3][1] + pos->z * vmatrix.matrix[3][2] + vmatrix.matrix[3][3];
		if (w < 0.1f)
			return false;

		screenVec.x /= w;
		screenVec.y /= w;

		D3DVIEWPORT9 viewPort;
		pDevice->GetViewport(&viewPort);

		out->x = (viewPort.Width / 2) + ((screenVec.x / 2) * viewPort.Width + 0.5f);
		out->y = (viewPort.Height / 2) - ((screenVec.y / 2) * viewPort.Height + 0.5f);
		out->z = 0.0f;

		return true;
	}

	inline float GetDistance3D(flVec3 pos0, flVec3 pos1)
	{
		return sqrt(
				pow(double(pos1.x) - double(pos0.x), 2.0) +
				pow(double(pos1.y) - double(pos0.y), 2.0) +
				pow(double(pos1.z) - double(pos0.z), 2.0)
			);
	}
}


#endif