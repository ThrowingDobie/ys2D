#include "stdafx.h"
#include "cNPC.h"
#include <cmath>

cNPC::cNPC()
{
	NPC_Host = nullptr;
	NPC_Host_A = nullptr;
	NPC_Host_B = nullptr;
	NPC_HostPos = { 1300, 1050 };
	delta = 0;

}


cNPC::~cNPC()
{
	SafeRelease(NPC_Host);
	SafeRelease(NPC_Host_A);
	SafeRelease(NPC_Host_B);
}

int cNPC::GetCrushOn(int a)
{
	return CrushOn;
}

void cNPC::Update()
{
	if (delta < 50) delta++;
	else if (delta >= 15) delta = 0;

	Dis = sqrt((NPC_HostPos.x - PlayerPos.x)*(NPC_HostPos.x - PlayerPos.x) +
		(NPC_HostPos.y - PlayerPos.y)*(NPC_HostPos.y - PlayerPos.y));

	if (NPC_Host_Speech == 2)
	{
		if (bEnt)
		{
			NPC_Host_Speech = 3;
			MainTile[64][57] = 0;
			MainTile[65][57] = 0;
			MainTile[66][57] = 0;
		}
	}

	else if (NPC_Host_Speech == 1)
	{
		if (bEnt)
		{
			NPC_Host_Speech = 2;
		}
	}

	else if (Dis <= 40 && NPC_Host_Speech == 0)
	{
		NPC_Host_Speech = 1;
	}

	else if (Dis > 40)
	{
		NPC_Host_Speech = 0;
	}



	

}
void cNPC::SpeechRender(cD2DRenderer& renderer)
{
	if (NPC_Host_Speech == 1)
	{
		if (NPC_Host_A != nullptr);
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Resolution.x / 2 - 351 / 2,
				Resolution.y / 2 - 129 / 2,
				Resolution.x / 2 + 351 / 2,
				Resolution.y / 2 + 129 / 2
				);
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 351, 129);
			renderer.GetRenderTarget()->DrawBitmap(NPC_Host_A, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}

	if (NPC_Host_Speech == 2)
	{
		if (NPC_Host_B != nullptr);
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Resolution.x / 2 - 278 / 2,
				Resolution.y / 2 - 129 / 2,
				Resolution.x / 2 + 278 / 2,
				Resolution.y / 2 + 129 / 2
				);
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 278, 129);
			renderer.GetRenderTarget()->DrawBitmap(NPC_Host_B, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}
}

void cNPC::Render(cD2DRenderer& renderer)
{
	if (NPC_Host != nullptr);
	{
		D2D1_SIZE_U size = renderer.GetRenderTargetSize();
		::D2D1_RECT_F dxArea = ::D2D1::RectF(
			NPC_HostPos.x - 16 + Screen.x,
			NPC_HostPos.y - 52 + Screen.y,
			NPC_HostPos.x + 16 + Screen.x,
			NPC_HostPos.y + Screen.y);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 30, 48);
		renderer.GetRenderTarget()->DrawBitmap(NPC_Host, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}




	WCHAR str[128];
	wsprintf(str, L"0 = %d", delta);
	UINT32 cTextLength_c = (UINT32)wcslen(str);

	D2D1_RECT_F layoutRectc = D2D1::RectF(830, 250, 1130, 350);

	renderer.GetRenderTarget()->DrawTextW(
		str,
		cTextLength_c,
		renderer.GetTextFormat(),
		layoutRectc,
		renderer.GetBrush());


}
void cNPC::LoadImages(cD2DRenderer& renderer, HWND hWnd)
{
	NPC_Host = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/NPC/NPC_Host.png");
	NPC_Host_A = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/NPC/NPC_Host_A.png");
	NPC_Host_B = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/NPC/NPC_Host_B.png");
}