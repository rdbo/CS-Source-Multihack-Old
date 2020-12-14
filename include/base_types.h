#pragma once
#ifndef BASE_TYPES_H
#define BASE_TYPES_H

typedef struct iVec2
{
	int x, y;
}iVec2;

typedef struct iVec3
{
	int x, y, z;
}iVec3;

typedef struct iVec4
{
	int x, y, z, w;
}iVec4;

typedef struct flVec2
{
	float x, y;
}flVec2;

typedef struct flVec3
{
	float x, y, z;
}flVec3;

typedef struct flVec4
{
	float x, y, z, w;
}flVec4;

typedef struct iColor3
{
	int r, g, b;
}iColor3;

typedef struct iColor4
{
	int r, g, b, a;
}iColor4;

typedef struct flColor3
{
	float r, g, b;
}flColor3;

typedef struct flColor4
{
	float r, g, b, a;
}flColor4;

#endif