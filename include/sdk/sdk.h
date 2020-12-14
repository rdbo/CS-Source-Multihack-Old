#pragma once
#ifndef SDK_H
#define SDK_H

#include <iostream>
#include <cstdint>
#include <libmem++/libmem.hpp>

typedef struct
{
	int x, y;
}iVec2;

typedef struct
{
	int x, y, z;
}iVec3;

typedef struct
{
	int x, y, z, w;
}iVec4;

typedef struct
{
	float x, y;
}flVec2;

typedef struct
{
	float x, y, z;
}flVec3;

typedef struct
{
	float x, y, z, w;
}flVec4;

typedef struct
{
	int r, g, b;
}iColor3;

typedef struct
{
	int r, g, b, a;
}iColor4;

typedef struct
{
	float r, g, b;
}flColor3;

typedef struct
{
	float r, g, b, a;
}flColor4;

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

	class CSEntityList
	{
		public:
		CSPlayer Entity;
		char pad[Offsets::dwDist];
		CSEntityList* pNext;
	};

	struct ViewMatrix
	{
		float Matrix[4][4];
	};
}


#endif