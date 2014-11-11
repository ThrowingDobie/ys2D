#include "stdafx.h"
#include "cMapObject.h"


cMapObject::cMapObject()
{
	TileLine = nullptr;
	WoodenBuilding_s = nullptr;
	WoodenBuilding_b = nullptr;
	StoneBuilding_s = nullptr;
	StoneBuilding_b = nullptr;
	Fence = nullptr;

	rWoodenBuilding_s = { 0, 0, 384, 280 };
	rWoodenBuilding_b;
	rStoneBuilding_s = { 0, 0, 384, 284 };
	rStoneBuilding_b = { 0, 0, 865, 383 };
	rFence = { 0, 0, 224, 233 };
}


cMapObject::~cMapObject()
{
	SafeRelease(TileLine);
	SafeRelease(WoodenBuilding_s);
	SafeRelease(WoodenBuilding_b);
	SafeRelease(StoneBuilding_s);
	SafeRelease(StoneBuilding_b);
	SafeRelease(Fence);
}

void cMapObject::Update()
{
	if (MouseLD.x > 28 && MouseLD.x < 771 && MouseLD.y>28 && MouseLD.y < 431)
	{
		if (MouseState.x == 1)
		{
			int A = (MouseLD.x - Screen.x) / TileSize.x;
			int B = (MouseLD.y - Screen.y) / TileSize.y;
			MainTile[A][B] = 1;
		}
	}

	if (MouseRD.x > 28 && MouseRD.x < 771 && MouseRD.y>28 && MouseRD.y < 431)
	{
		if (MouseState.y == 1)
		{
			int A = (MouseRD.x - Screen.x) / TileSize.x;
			int B = (MouseRD.y - Screen.y) / TileSize.y;
			MainTile[A][B] = 0;
		}
	}


}

void cMapObject::Render(cD2DRenderer& renderer)
{
	//타일 찍는것처럼 범위지정해서 나머지 안보이게 하기 

	if (TileLine != nullptr);
	{
		::D2D1_RECT_F dxArea = ::D2D1::RectF(
			MouseMove.x,
			MouseMove.y,
			MouseMove.x + TileSize.x,
			MouseMove.y + TileSize.y);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, TileSize.x, TileSize.y);
		renderer.GetRenderTarget()->DrawBitmap(TileLine, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	int a, b = 0;
	RECT RC;
	RC.left = g_Camera.x / TileSize.x;
	RC.right = g_Camera.x / TileSize.x + (Resolution.x / TileSize.x);
	RC.top = g_Camera.y / TileSize.y;
	RC.bottom = g_Camera.y / TileSize.y + (Resolution.y / TileSize.y);

	for (b = 0; b < StageA_Size.y / TileSize.y; b++)
	{
		for (a = 0; a < StageA_Size.x / TileSize.y; a++)
		{
			if (a > RC.left && a < RC.right && b > RC.top && b < RC.bottom)
			{
				if (MainTile[a][b] != 0)
				{
					if (TileLine != nullptr);
					{
						::D2D1_RECT_F dxArea = ::D2D1::RectF(
							Screen.x + a*TileSize.x,
							Screen.y + b*TileSize.y,
							Screen.x + a*TileSize.x + TileSize.x,
							Screen.y + b*TileSize.y + TileSize.y);
						::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, TileSize.x, TileSize.y);
						renderer.GetRenderTarget()->DrawBitmap(TileLine, dxArea, 1.0f,
							D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
							srcArea);
					}
				}
			}
		}
	}
}

void cMapObject::DataRender(cD2DRenderer& renderer)
{
	WCHAR str[128];
	wsprintf(str, L"Player = %d,%d", PlayerPos.x, PlayerPos.y);
	UINT32 cTextLength_ = (UINT32)wcslen(str);

	D2D1_RECT_F layoutRect = D2D1::RectF(830, 0, 1130, 100);

	renderer.GetRenderTarget()->DrawTextW(
		str,
		cTextLength_,
		renderer.GetTextFormat(),
		layoutRect,
		renderer.GetBrush());

	str[128];
	wsprintf(str, L"Camera = %d,%d", g_Camera.x, g_Camera.y);
	UINT32 cTextLength_a = (UINT32)wcslen(str);

	D2D1_RECT_F layoutRecta = D2D1::RectF(830, 50, 1130, 150);

	renderer.GetRenderTarget()->DrawTextW(
		str,
		cTextLength_a,
		renderer.GetTextFormat(),
		layoutRecta,
		renderer.GetBrush());

	str[128];
	wsprintf(str, L"Screen = %d,%d", Screen.x, Screen.y);
	UINT32 cTextLength_b = (UINT32)wcslen(str);

	D2D1_RECT_F layoutRectb = D2D1::RectF(830, 100, 1130, 200);

	renderer.GetRenderTarget()->DrawTextW(
		str,
		cTextLength_b,
		renderer.GetTextFormat(),
		layoutRectb,
		renderer.GetBrush());


}

void cMapObject::FrontBuildingRender(cD2DRenderer& renderer)
{
	Miracle = 0.3;
	if (PlayerPos.x > 145-15 && PlayerPos.x < 145 + 400)
	{
		if (PlayerPos.y > 235 + 100 && PlayerPos.y < 235 + 330) Miracle = 1;
	}
	if (PlayerPos.x > 1585 - 15 && PlayerPos.x < 1585 + 400)
	{
		if (PlayerPos.y > 995 + 100 && PlayerPos.y < 995 + 330) Miracle = 1;
	}
	if (PlayerPos.x > 1545 - 15 && PlayerPos.x < 1545 + 400)
	{
		if (PlayerPos.y > 95 + 100 && PlayerPos.y < 95 + 330) Miracle = 1;
	}
	if (PlayerPos.x > 1105 - 15 && PlayerPos.x < 1105 + 400)
	{
		if (PlayerPos.y > 695 + 100 && PlayerPos.y < 695 + 330) Miracle = 1;
	}
	if (PlayerPos.x > 205 - 15 && PlayerPos.x < 205 + 400)
	{
		if (PlayerPos.y > 600 + 100 && PlayerPos.y < 600 + 330) Miracle = 1;
	}
	if (PlayerPos.x > 945 - 15 && PlayerPos.x < 945 + 400)
	{
		if (PlayerPos.y > 280 + 100 && PlayerPos.y < 280 + 330) Miracle = 1;
	}
	if (PlayerPos.x > 130 - 15 && PlayerPos.x < 130 + 890)
	{
		if (PlayerPos.y > 1020 + 200 && PlayerPos.y < 1020 + 430) Miracle = 1;
	}
	if (PlayerPos.x > 1205 - 15 && PlayerPos.x < 1205 + 400)
	{
		if (PlayerPos.y > 1105 + 100 && PlayerPos.y < 1105 + 330) Miracle = 1;
	}

	Build(renderer, WoodenBuilding_s, rWoodenBuilding_s, 145, 235);
	Build(renderer, WoodenBuilding_s, rWoodenBuilding_s, 1585, 995);
	Build(renderer, WoodenBuilding_s, rWoodenBuilding_s, 1545, 95);
	Build(renderer, WoodenBuilding_s, rWoodenBuilding_s, 1105, 695);
	Build(renderer, StoneBuilding_s, rStoneBuilding_s, 205, 600);
	Build(renderer, StoneBuilding_s, rStoneBuilding_s, 945, 280);
	Build(renderer, StoneBuilding_b, rStoneBuilding_b, 130, 1020);
	Build(renderer, Fence, rFence, 1205, 1105);
}
void cMapObject::BackBuildingRender(cD2DRenderer& renderer)
{

}
void cMapObject::LoadImages(cD2DRenderer& renderer, HWND hWnd)
{
	TileLine = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Tile/TileLine.png");
	WoodenBuilding_s = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Object/WoodenBuilding_s.png");
	//WoodenBuilding_b = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Object/WoodenBuilding_b.png");
	StoneBuilding_s = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Object/StoneBuilding_s.png");
	StoneBuilding_b = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Object/StoneBuilding_b.png");
	Fence = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Object/Fence.png");
	::InvalidateRect(hWnd, NULL, TRUE);
}

void cMapObject::Build(cD2DRenderer& renderer, ID2D1Bitmap* A, D2D1_RECT_F &RT, int posx, int posy)
{


	RECT PlayerConst;
	RECT ObjectConst; // 시야 상수
	float a, b, c, d = 0;
	PlayerConst.left = (PlayerPos.x + 16) - posx;
	PlayerConst.top = (PlayerPos.y) - posy;
	PlayerConst.right = (PlayerPos.x - 16) - posx;
	PlayerConst.bottom = (PlayerPos.y - 47) - posy;
	a = PlayerConst.left / RT.right;
	b = PlayerConst.top / RT.bottom;
	c = PlayerConst.right / RT.right;
	d = PlayerConst.bottom / RT.bottom;
	// 외곽 보정
	if (PlayerPos.x >= posx-30 && PlayerPos.x <= posx+30) c = 0;
	if (PlayerPos.y >= posy-30 && PlayerPos.y <= posy+30) d = 0;

	if (a >= 1) a = 1;
	if (b >= 1) b = 1;
	float x, y = 0;
	ObjectConst.left = (g_Camera.x + Resolution.x) - (posx);
	ObjectConst.top = (g_Camera.y + Resolution.y) - (posy);
	x = ObjectConst.left / RT.right;
	y = ObjectConst.top / RT.bottom;
	if (x >= 1) x = 1;
	if (y >= 1) y = 1;


	if (PlayerConst.left > 0 && PlayerConst.top > 0)
	{
		if (A != nullptr)
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				(Screen.x + RT.right*c) + posx,
				(Screen.y + RT.bottom*d) + posy,
				(Screen.x + RT.right*a) + posx,
				(Screen.y + RT.bottom*b) + posy);
			::D2D1_RECT_F srcArea = ::D2D1::RectF(
				RT.right*c,
				RT.bottom*d,
				RT.right*a,
				RT.bottom*b);

			renderer.GetRenderTarget()->DrawBitmap(A, dxArea, Miracle,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}

	}

	if (a >= 0 &&
		b >= 0 &&
		c <= 1 &&
		d <= 1)
	{
		if (A != nullptr)
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Screen.x + posx,
				Screen.y + posy,
				(Screen.x + RT.right*x) + posx,
				(Screen.y + RT.bottom*d) + posy);
			::D2D1_RECT_F srcArea = ::D2D1::RectF(
				0,
				0,
				RT.right*x,
				RT.bottom*d);

			renderer.GetRenderTarget()->DrawBitmap(A, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			dxArea = ::D2D1::RectF(
				Screen.x + posx,
				Screen.y + posy,
				(Screen.x + RT.right*c) + posx,
				(Screen.y + RT.bottom*y) + posy);
			srcArea = ::D2D1::RectF(
				0,
				0,
				RT.right*c,
				RT.bottom*y);

			renderer.GetRenderTarget()->DrawBitmap(A, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			dxArea = ::D2D1::RectF(
				Screen.x + posx,
				(Screen.y + RT.bottom*b) + posy,
				(Screen.x + RT.right*x) + posx,
				(Screen.y + RT.bottom*y) + posy);
			srcArea = ::D2D1::RectF(
				0,
				(RT.bottom*b),
				RT.right*x,
				RT.bottom*y);

			renderer.GetRenderTarget()->DrawBitmap(A, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			dxArea = ::D2D1::RectF(
				(Screen.x + RT.right*a) + posx,
				Screen.y + posy,
				(Screen.x + RT.right*x) + posx,
				(Screen.y + RT.bottom*y) + posy);
			srcArea = ::D2D1::RectF(
				(RT.right*a),
				0,
				RT.right*x,
				RT.bottom*y);

			renderer.GetRenderTarget()->DrawBitmap(A, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		
	}
	else if (ObjectConst.left >= 0 && ObjectConst.top >= 0)
	{
		if (A != nullptr)
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Screen.x + posx,
				Screen.y + posy,
				(Screen.x + RT.right*x) + posx,
				(Screen.y + RT.bottom*y) + posy);
			::D2D1_RECT_F srcArea = ::D2D1::RectF(
				0,
				0,
				RT.right*x,
				RT.bottom*y);

			renderer.GetRenderTarget()->DrawBitmap(A, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}

	
}