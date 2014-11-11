#include "stdafx.h"
#include "cInven.h"


cInven::cInven()
{
	InvenMain = nullptr;
	Potion = nullptr;
	Potion_Select = nullptr;
	InvenSelectingLine = nullptr;
	InvenSelectedLine = nullptr;
	ReturnLine = nullptr;

	KeepPotion = true;
	//SetPotion = false;
	Potion_Pos = { 56, 105, 101, 150 };
	ReturnPos = { 264.0f, 392.0f, 380.0f, 425.0f };
	//MouseOn = 0;
}


cInven::~cInven()
{
	SafeRelease(InvenMain);
	SafeRelease(Potion);
	SafeRelease(Potion_Select);
	SafeRelease(InvenSelectingLine);
	SafeRelease(InvenSelectedLine);
	SafeRelease(ReturnLine);
}

void cInven::Update()
{

}
void cInven::RenderUpdate()
{
	if (MouseMove.x >= ReturnPos.left &&
		MouseMove.x <= ReturnPos.right &&
		MouseMove.y >= ReturnPos.top &&
		MouseMove.y <= ReturnPos.bottom)
	{
		MouseOnR = 1;
	}
	else MouseOnR = 0;

	if (MouseLD.x >= ReturnPos.left &&
		MouseLD.x <= ReturnPos.right &&
		MouseLD.y >= ReturnPos.top &&
		MouseLD.y <= ReturnPos.bottom)
	{
		MouseOnR = 99;
	}

	if (MouseOnR == 99)
	{
		Stage = 1;
		MouseMove = { 0, 0 };
		MouseLD = { 0, 0 };
		MouseRD = { 0, 0 };
		MouseState = { 0, 0 };
	}

	if (KeepPotion)
	{
		if (MouseMove.x >= Potion_Pos.left &&
			MouseMove.x <= Potion_Pos.right &&
			MouseMove.y >= Potion_Pos.top &&
			MouseMove.y <= Potion_Pos.bottom)
		{
			MouseOn = 1;
		}
		else MouseOn = 0;

		if (MouseLD.x >= Potion_Pos.left &&
			MouseLD.x <= Potion_Pos.right &&
			MouseLD.y >= Potion_Pos.top &&
			MouseLD.y <= Potion_Pos.bottom)
		{
			MouseOnP = 2;
			SetPotion = true;
		}

		if (MouseRD.x >= Potion_Pos.left &&
			MouseRD.x <= Potion_Pos.right &&
			MouseRD.y >= Potion_Pos.top &&
			MouseRD.y <= Potion_Pos.bottom)
		{
			MouseOnP = 0;
			MouseRD = { 0, 0 };
			MouseLD = { 0, 0 };
		}
	}


}
void cInven::Render(cD2DRenderer& renderer)
{


	if (KeepPotion)
	{
		if (Potion != nullptr);
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(0, 0, Resolution.x, Resolution.y);
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 800, 600);
			renderer.GetRenderTarget()->DrawBitmap(Potion, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}

		if (MouseOn == 1)
		{
			if (InvenSelectingLine != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = Potion_Pos;
				::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 45, 45);
				renderer.GetRenderTarget()->DrawBitmap(InvenSelectingLine, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}

		if (MouseOnP == 2)
		{
			if (InvenSelectedLine != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Potion_Pos.left,
					Potion_Pos.top,
					Potion_Pos.right,
					Potion_Pos.bottom+3);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 45, 48);
				renderer.GetRenderTarget()->DrawBitmap(InvenSelectedLine, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
	}

	else if (KeepPotion == false)
	{
		if (InvenMain != nullptr);
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(0, 0, Resolution.x, Resolution.y);
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 800, 600);
			renderer.GetRenderTarget()->DrawBitmap(InvenMain, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}

	if (MouseOnR == 1)
	{
		if (ReturnLine != nullptr)
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ReturnPos;
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 117, 34);
			renderer.GetRenderTarget()->DrawBitmap(ReturnLine, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}

}

void cInven::LoadImages(cD2DRenderer& renderer, HWND hWnd)
{
	InvenMain = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Inven/InvenMain.png");
	Potion = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Inven/Potion.png");
	Potion_Select = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Inven/Potion_Select.png");
	InvenSelectingLine = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Inven/InvenSelectingLine.png");
	InvenSelectedLine = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Inven/InvenSelectedLine.png");
	ReturnLine = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Inven/ReturnLine.png");
}