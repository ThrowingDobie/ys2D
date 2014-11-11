#include "stdafx.h"
#include "cInterFace.h"

cInterFace::cInterFace()
{
	Edge = nullptr;
	MenuBarMain = nullptr;
	MenuBar_Load = nullptr;
	MenuBar_Save = nullptr;
	MenuBar_Equip = nullptr;
	MenuBar_Inven = nullptr;
	MenuBar_Status = nullptr;
	MenuBar_Option = nullptr;
	//EmptyHpBar = nullptr;

	MenuBar1 = { 160, 555, 238, 585 };
	MenuBar2 = { 240, 555, 318, 585 };
	MenuBar3 = { 320, 555, 398, 585 };
	MenuBar4 = { 400, 555, 478, 585 };
	MenuBar5 = { 480, 555, 558, 585 };
	MenuBar6 = { 560, 555, 638, 585 };
	MenuBar7 = { 147, 542, 651, 596 };
	MenuBar0 = { 0, 0, 403, 43 };
}


cInterFace::~cInterFace()
{
	SafeRelease(Edge);
	SafeRelease(MenuBar_Load);
	SafeRelease(MenuBar_Save);
	SafeRelease(MenuBar_Equip);
	SafeRelease(MenuBar_Inven);
	SafeRelease(MenuBar_Status);
	SafeRelease(MenuBar_Option);
	SafeRelease(MenuBarMain);
	SafeRelease(EmptyHpBar);

}

void cInterFace::Update()
{
	//147.542.651.596
	//100,500,700,800

	if (MouseState.x == 0)
	{
		MouseLD = { 0, 0 };
	}

	if ((MouseMove.x >= 0) &&
		(MouseMove.x <= 800) &&
		(MouseMove.y >= 500) &&
		(MouseMove.y <= 800))
		MenuBarView = 1;
	else MenuBarView = 0;

	if (MenuBarView)
	{
		delta += 2;
		if (delta >= 10) delta = 10;
	}
	else
	{
		delta -= 2;
		if (delta < 0) delta = 0;
	}

	//  Load 
	if ((MouseMove.x >= 160) && (MouseMove.x <= 238) && (MouseMove.y >= 555) && (MouseMove.y <= 585))
	{
		MenuBar = 1;
		//if (MouseLD.x) Stage = 92;
	}
	// Save
	else if ((MouseMove.x >= 240) && (MouseMove.x <= 318) && (MouseMove.y >= 555) && (MouseMove.y <= 585))
	{
		MenuBar = 2;
		//if (MouseLD.x) Stage = 93;
	}
	// Equip 
	else if ((MouseMove.x >= 320) && (MouseMove.x <= 398) && (MouseMove.y >= 555) && (MouseMove.y <= 585))
	{
		MenuBar = 3;
		if (MouseLD.x)
		{
			Stage = 94;
			MouseMove = { 0, 0 };
			MouseLD = { 0, 0 };
			MouseRD = { 0, 0 };
			MouseState = { 0, 0 };
		}
	}
	// Inven
	else if ((MouseMove.x >= 400) && (MouseMove.x <= 478) && (MouseMove.y >= 555) && (MouseMove.y <= 585))
	{
		MenuBar = 4;
		if (MouseLD.x)
		{
			Stage = 95;
			MouseMove = { 0, 0 };
			MouseLD = { 0, 0 };
			MouseRD = { 0, 0 };
			MouseState = { 0, 0 };
		}
	}
	// Status
	else if ((MouseMove.x >= 480) && (MouseMove.x <= 558) && (MouseMove.y >= 555) && (MouseMove.y <= 585))
	{
		MenuBar = 5;
		//if (MouseLD.x) Stage = 96;
	}
	// Option
	else if ((MouseMove.x >= 560) && (MouseMove.x <= 638) && (MouseMove.y >= 555) && (MouseMove.y <= 585))
	{
		MenuBar = 6;
		if (MouseLD.x)
		{
			Stage = 97;
			MouseMove = { 0, 0 };
			MouseLD = { 0, 0 };
			MouseRD = { 0, 0 };
			MouseState = { 0, 0 };
		}
	}
	// MenuBar
	else MenuBar = 0;
}

void cInterFace::Render(cD2DRenderer& renderer)
{
	if (Edge != nullptr);
	{
		D2D1_SIZE_U size = renderer.GetRenderTargetSize();
		::D2D1_RECT_F dxArea = ::D2D1::RectF(0, 0, 800, 600);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 800, 600);
		renderer.GetRenderTarget()->DrawBitmap(Edge, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
}
void cInterFace::MenuBarRender(cD2DRenderer& renderer)
{
	if (delta == 10)
	{
		if (MenuBar == 1)
		{
			if (MenuBar_Load != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = MenuBar7;
				::D2D1_RECT_F srcArea = MenuBar0;
				renderer.GetRenderTarget()->DrawBitmap(MenuBar_Load, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		else if (MenuBar == 2)
		{
			if (MenuBar_Save != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = MenuBar7;
				::D2D1_RECT_F srcArea = MenuBar0;
				renderer.GetRenderTarget()->DrawBitmap(MenuBar_Save, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		else if (MenuBar == 3)
		{
			if (MenuBar_Equip != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = MenuBar7;
				::D2D1_RECT_F srcArea = MenuBar0;
				renderer.GetRenderTarget()->DrawBitmap(MenuBar_Equip, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		else if (MenuBar == 4)
		{
			if (MenuBar_Inven != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = MenuBar7;
				::D2D1_RECT_F srcArea = MenuBar0;
				renderer.GetRenderTarget()->DrawBitmap(MenuBar_Inven, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		else if (MenuBar == 5)
		{
			if (MenuBar_Status != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = MenuBar7;
				::D2D1_RECT_F srcArea = MenuBar0;
				renderer.GetRenderTarget()->DrawBitmap(MenuBar_Status, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		else if (MenuBar == 6)
		{
			if (MenuBar_Option != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = MenuBar7;
				::D2D1_RECT_F srcArea = MenuBar0;
				renderer.GetRenderTarget()->DrawBitmap(MenuBar_Option, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		else if (MenuBar == 0)
		{
			if (MenuBarMain != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = MenuBar7;
				::D2D1_RECT_F srcArea = MenuBar0;
				renderer.GetRenderTarget()->DrawBitmap(MenuBarMain, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
	}

	else if (delta)
	{
		if (MenuBarMain != nullptr);
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = { 147, 596 - delta * 5.7, 651, 596 };
			::D2D1_RECT_F srcArea = { 0, 0, 403, delta*4.3 };
			renderer.GetRenderTarget()->DrawBitmap(MenuBarMain, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}

}
void cInterFace::LoadImages(cD2DRenderer& renderer, HWND hWnd)
{
	Edge = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/InterFace/Edge.png");
	MenuBarMain = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/InterFace/MenuBar.png");
	MenuBar_Load = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/InterFace/MenuBar_LoadOn.png");
	MenuBar_Save = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/InterFace/MenuBar_SaveOn.png");
	MenuBar_Equip = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/InterFace/MenuBar_EquipOn.png");
	MenuBar_Inven = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/InterFace/MenuBar_InvenOn.png");
	MenuBar_Status = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/InterFace/MenuBar_StatusOn.png");
	MenuBar_Option = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/InterFace/MenuBar_OptionOn.png");
	//MenuBar_Option = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/InterFace/EmptyHpBar.png");
	::InvalidateRect(hWnd, NULL, TRUE);
}