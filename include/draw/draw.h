#pragma once
#ifndef DRAW_H
#define DRAW_H

#include <d3d9.h>
#include <d3dx9.h>
#include <base_types.h>

namespace Draw
{
	inline void Line(iVec2 src, iVec2 dst, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
	{
		ID3DXLine* LineL;
		D3DXCreateLine(pDevice, &LineL);

		D3DXVECTOR2 Line[2];
		Line[0] = D3DXVECTOR2(src.x, src.y);
		Line[1] = D3DXVECTOR2(dst.x, dst.y);
		LineL->SetWidth(thickness);
		LineL->Draw(Line, 2, color);
		LineL->Release();
	}

	inline void Text(LPCSTR str, int x, int y, size_t dist, D3DCOLOR color, LPD3DXFONT pFont)
	{
		RECT rect;
		pFont->DrawTextA(NULL, str, strlen(str), &rect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));
		int size = rect.right -= rect.left;
		rect.left = x - size / 2;
		rect.right = x + size / 2;
		rect.top = y - dist;
		rect.bottom = rect.top + size;
		pFont->DrawTextA(NULL, str, -1, &rect, DT_NOCLIP, color);
	}

	inline void Rectangle(int x, int y, int w, int h, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
	{
		Line({ x, y }, { w, y }, thickness, color, pDevice);
		Line({ w, y }, { w, h }, thickness, color, pDevice);
		Line({ w, h }, { x, h }, thickness, color, pDevice);
		Line({ x, h }, { x, y }, thickness, color, pDevice);
	}

	inline void FilledRectangle(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
	{
		D3DRECT BarRect = { x, y, x + w, y + h };
		pDevice->Clear(1, &BarRect, D3DCLEAR_TARGET | D3DCLEAR_TARGET, color, 0, 0);
	}
}

#endif