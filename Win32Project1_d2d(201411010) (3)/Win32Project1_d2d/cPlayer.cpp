#include "stdafx.h"
#include "cPlayer.h"
#include "cMonster.h"
#include "cGameManager.h"

cMonster pMonster;
extern cGameManager* g_pGameManager;

cPlayer::cPlayer()
{
	Adol = nullptr;
	PlayerHpBar = nullptr;
	PlayerEffect = nullptr;
	PlayerPos = { 800, 850 };

	PlayerFocus = { 0, 0, 0, 0 };

	FocusLeft = { 1, 637, 32, 688 };
	FocusRight = { 1, 425, 32, 476 };
	FocusTop = { 1, 531, 32, 582 };
	FocusBottom = { 1, 743, 32, 794 };

	Focus1 = { 1, 690, 32, 741 };
	Focus3 = { 1, 796, 32, 847 };
	Focus7 = { 1, 584, 32, 635 };
	Focus9 = { 1, 478, 32, 529 };

	WayLeft = { 1, 213, 32, 264 };
	WayRight = { 1, 1, 32, 52 };
	WayTop = { 1, 107, 32, 158 };
	WayBottom = { 1, 319, 32, 370 };

	Way1 = { 1, 266, 32, 317 };
	Way3 = { 1, 372, 32, 423 };
	Way7 = { 1, 160, 32, 211 };
	Way9 = { 1, 54, 32, 105 };

	PlayerSpeed = 10;
	PlayerHp = 100;
	PlayerDefense = 1.0;
	PlayerAttack = 1.0;

	AdolRatio.x = 33.0f;

	EffectRect(PlayerEffect1, 57, 334);
	EffectRect(PlayerEffect2, 186, 334);
	EffectRect(PlayerEffect3, 313, 334);
	EffectRect(PlayerEffect4, 441, 334);
	EffectRect(PlayerEffect5, 569, 334);
	EffectRect(PlayerEffect6, 698, 334);
	EffectRect(PlayerEffect7, 826, 334);
}


cPlayer::~cPlayer()
{
	SafeRelease(Adol);
	SafeRelease(PlayerHpBar);
	SafeRelease(PlayerEffect);
}

void cPlayer::KeyDown(DWORD dwKey)
{
	if (dwKey == VK_RIGHT)
		bRight = true;
	if (dwKey == VK_LEFT)
		bLeft = true;
	if (dwKey == VK_DOWN)
		bDown = true;
	if (dwKey == VK_UP)
		bUp = true;
}

void cPlayer::KeyUp(DWORD dwKey)
{
	if (dwKey == VK_RIGHT)
		bRight = false;
	if (dwKey == VK_LEFT)
		bLeft = false;
	if (dwKey == VK_DOWN)
		bDown = false;
	if (dwKey == VK_UP)
		bUp = false;
}

void cPlayer::Update()
{
	TileTypeL = MainTile[((PlayerPos.x - 10) / TileSize.x)][(PlayerPos.y) / TileSize.y];
	TileTypeR = MainTile[((PlayerPos.x + 10) / TileSize.x)][(PlayerPos.y) / TileSize.y];
	TileTypeU = MainTile[((PlayerPos.x) / TileSize.x)][(PlayerPos.y - 10) / TileSize.y];
	TileTypeD = MainTile[((PlayerPos.x) / TileSize.x)][(PlayerPos.y + 10) / TileSize.y];

	g_pGameManager->GetCrushMonster(State);

	for (int a = 0; a < 10; a++)
	{
		if (State[a] > 0 && State[a]<=3)
		{
			CrushOn = State[a];
			break;
		}
		else
		{
			CrushOn = 0;
		}
	}

	if (CrushOn == 2)
	{
		delta += 1;
		if (delta > 8) delta = 0;
	}
	else delta = 0;


}


void cPlayer::Temp(int x, int y)
{
	PlayerPos.x = x;
	PlayerPos.y = y;
}

void cPlayer::EffectRect(D2D1_RECT_F &RT, int x, int y)
{
	RT.left = x - 40;
	RT.right = x + 40;
	RT.top = y - 35;
	RT.bottom = y + 35;
}

void cPlayer::EffectRender(cD2DRenderer& renderer)
{

	D2D1_RECT_F EffectPivot_p;
	EffectPivot_p = { PlayerPos.x - 30, PlayerPos.y - 50, PlayerPos.x + 30, PlayerPos.y };

	if (CrushOn == 2)
	{
		if (delta == 0)
		{
			if (PlayerEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_p.left,
					Screen.y + EffectPivot_p.top,
					Screen.x + EffectPivot_p.right,
					Screen.y + EffectPivot_p.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					PlayerEffect1.left,
					PlayerEffect1.top,
					PlayerEffect1.right,
					PlayerEffect1.bottom);
				renderer.GetRenderTarget()->DrawBitmap(PlayerEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (delta == 1)
		{
			if (PlayerEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_p.left,
					Screen.y + EffectPivot_p.top,
					Screen.x + EffectPivot_p.right,
					Screen.y + EffectPivot_p.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					PlayerEffect2.left,
					PlayerEffect2.top,
					PlayerEffect2.right,
					PlayerEffect2.bottom);
				renderer.GetRenderTarget()->DrawBitmap(PlayerEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (delta == 2)
		{
			if (PlayerEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_p.left,
					Screen.y + EffectPivot_p.top,
					Screen.x + EffectPivot_p.right,
					Screen.y + EffectPivot_p.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					PlayerEffect3.left,
					PlayerEffect3.top,
					PlayerEffect3.right,
					PlayerEffect3.bottom);
				renderer.GetRenderTarget()->DrawBitmap(PlayerEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (delta == 3)
		{
			if (PlayerEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_p.left,
					Screen.y + EffectPivot_p.top,
					Screen.x + EffectPivot_p.right,
					Screen.y + EffectPivot_p.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					PlayerEffect4.left,
					PlayerEffect4.top,
					PlayerEffect4.right,
					PlayerEffect4.bottom);
				renderer.GetRenderTarget()->DrawBitmap(PlayerEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (delta == 4)
		{
			if (PlayerEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_p.left,
					Screen.y + EffectPivot_p.top,
					Screen.x + EffectPivot_p.right,
					Screen.y + EffectPivot_p.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					PlayerEffect5.left,
					PlayerEffect5.top,
					PlayerEffect5.right,
					PlayerEffect5.bottom);
				renderer.GetRenderTarget()->DrawBitmap(PlayerEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (delta == 5)
		{
			if (PlayerEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_p.left,
					Screen.y + EffectPivot_p.top,
					Screen.x + EffectPivot_p.right,
					Screen.y + EffectPivot_p.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					PlayerEffect6.left,
					PlayerEffect6.top,
					PlayerEffect6.right,
					PlayerEffect6.bottom);
				renderer.GetRenderTarget()->DrawBitmap(PlayerEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (delta == 6)
		{
			if (PlayerEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_p.left,
					Screen.y + EffectPivot_p.top,
					Screen.x + EffectPivot_p.right,
					Screen.y + EffectPivot_p.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					PlayerEffect7.left,
					PlayerEffect7.top,
					PlayerEffect7.right,
					PlayerEffect7.bottom);
				renderer.GetRenderTarget()->DrawBitmap(PlayerEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}

	}

}

void cPlayer::PlayerMove()
{
	if (CrushOn == 0) PlayerSpeed = 10;
	else if (CrushOn == 1) PlayerSpeed = 5;
	else if (CrushOn == 2) PlayerSpeed = 8;

	if (bLeft)
	{
		if (TileTypeL) Temp(PlayerPos.x, PlayerPos.y);
		else if (MonsterTile.left) Temp(PlayerPos.x, PlayerPos.y);
		else Temp(PlayerPos.x - PlayerSpeed, PlayerPos.y);
		PlayerFocus.left++;
		if (PlayerFocus.left == 4) PlayerFocus.left = 1;
		PlayerWay = 1;

	}
	if (bRight)
	{
		if (TileTypeR) Temp(PlayerPos.x, PlayerPos.y);
		else if (MonsterTile.right) Temp(PlayerPos.x, PlayerPos.y);
		else Temp(PlayerPos.x + PlayerSpeed, PlayerPos.y);
		PlayerFocus.right++;
		if (PlayerFocus.right == 4) PlayerFocus.right = 1;
		PlayerWay = 2;
	}
	if (bUp)
	{
		if (TileTypeU) Temp(PlayerPos.x, PlayerPos.y);
		else if (MonsterTile.top) Temp(PlayerPos.x, PlayerPos.y);
		else Temp(PlayerPos.x, PlayerPos.y - PlayerSpeed);
		PlayerFocus.top++;
		if (PlayerFocus.top == 4) PlayerFocus.top = 1;
		PlayerWay = 3;
	}
	if (bDown)
	{
		if (TileTypeD) Temp(PlayerPos.x, PlayerPos.y);
		else if (MonsterTile.bottom) Temp(PlayerPos.x, PlayerPos.y);
		else Temp(PlayerPos.x, PlayerPos.y + PlayerSpeed);
		PlayerFocus.bottom++;
		if (PlayerFocus.bottom == 4) PlayerFocus.bottom = 1;
		PlayerWay = 4;
	}
	


	if (PlayerPos.x < 0) PlayerPos.x = 0;
	if (PlayerPos.y < 0) PlayerPos.y = 0;
	if (PlayerPos.x > StageA_Size.x) PlayerPos.x = StageA_Size.x;
	if (PlayerPos.y > StageA_Size.y) PlayerPos.y = StageA_Size.y;
}

void cPlayer::Render(cD2DRenderer& renderer)
{
	D2D1_RECT_F Pivot_p;
	Pivot_p = { PlayerPos.x - 15, PlayerPos.y - 50, PlayerPos.x + 15, PlayerPos.y };

	Screen = { 0 - g_Camera.x, 0 - g_Camera.y };

	if (Adol != nullptr)
	{
		if (bLeft == 0 && bRight == 0 && bUp == 0 && bDown == 0)
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Screen.x + Pivot_p.left,
				Screen.y + Pivot_p.top,
				Screen.x + Pivot_p.right,
				Screen.y + Pivot_p.bottom);
			//::D2D1_RECT_F srcArea = ::D2D1::RectF(1.0f, 1.0f, 32.0f, 52.0f);
			::D2D1_RECT_F srcArea;
			if (PlayerWay == 0) srcArea = WayBottom;
			if (PlayerWay == 1) srcArea = WayLeft;
			if (PlayerWay == 2) srcArea = WayRight;
			if (PlayerWay == 3) srcArea = WayTop;
			if (PlayerWay == 4) srcArea = WayBottom;
			/*if (PlayerWay == 5) srcArea = Way7;
			if (PlayerWay == 6) srcArea = Way1;
			if (PlayerWay == 7) srcArea = Way9;
			if (PlayerWay == 8) srcArea = Way3;*/


			renderer.GetRenderTarget()->DrawBitmap(Adol, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		if (bLeft && bUp)
		{
			Focus7.left = Focus7.left + AdolRatio.x*PlayerFocus.left;
			Focus7.right = Focus7.right + AdolRatio.x*PlayerFocus.left;

			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Screen.x + Pivot_p.left,
				Screen.y + Pivot_p.top,
				Screen.x + Pivot_p.right,
				Screen.y + Pivot_p.bottom);
			::D2D1_RECT_F srcArea = Focus7;

			renderer.GetRenderTarget()->DrawBitmap(Adol, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			Focus7 = { 1, 584, 32, 635 };
		}
		else if (bRight && bUp)
		{
			Focus9.left = Focus9.left + AdolRatio.x*PlayerFocus.right;
			Focus9.right = Focus9.right + AdolRatio.x*PlayerFocus.right;
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Screen.x + Pivot_p.left,
				Screen.y + Pivot_p.top,
				Screen.x + Pivot_p.right,
				Screen.y + Pivot_p.bottom);
			::D2D1_RECT_F srcArea = Focus9;

			renderer.GetRenderTarget()->DrawBitmap(Adol, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			Focus9 = { 1, 478, 32, 529 };
		}
		else if(bLeft && bDown)
		{
			Focus1.left = Focus1.left + AdolRatio.x*PlayerFocus.left;
			Focus1.right = Focus1.right + AdolRatio.x*PlayerFocus.left;

			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Screen.x + Pivot_p.left,
				Screen.y + Pivot_p.top,
				Screen.x + Pivot_p.right,
				Screen.y + Pivot_p.bottom);
			::D2D1_RECT_F srcArea = Focus1;

			renderer.GetRenderTarget()->DrawBitmap(Adol, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			Focus1 = { 1, 690, 32, 741 };
		}
		else if(bRight && bDown)
		{
			Focus3.left = Focus3.left + AdolRatio.x*PlayerFocus.right;
			Focus3.right = Focus3.right + AdolRatio.x*PlayerFocus.right;
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Screen.x + Pivot_p.left,
				Screen.y + Pivot_p.top,
				Screen.x + Pivot_p.right,
				Screen.y + Pivot_p.bottom);
			::D2D1_RECT_F srcArea = Focus3;

			renderer.GetRenderTarget()->DrawBitmap(Adol, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			Focus3 = { 1, 796, 32, 847 };
		}

		else if(bLeft)
		{
			FocusLeft.left = FocusLeft.left + AdolRatio.x*PlayerFocus.left;
			FocusLeft.right = FocusLeft.right + AdolRatio.x*PlayerFocus.left;

			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Screen.x + Pivot_p.left,
				Screen.y + Pivot_p.top,
				Screen.x + Pivot_p.right,
				Screen.y + Pivot_p.bottom);
			::D2D1_RECT_F srcArea = FocusLeft;

			renderer.GetRenderTarget()->DrawBitmap(Adol, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			FocusLeft = { 1, 637, 32, 688 };
		}
		else if (bRight)
		{
			FocusRight.left = FocusRight.left + AdolRatio.x*PlayerFocus.right;
			FocusRight.right = FocusRight.right + AdolRatio.x*PlayerFocus.right;
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Screen.x + Pivot_p.left,
				Screen.y + Pivot_p.top,
				Screen.x + Pivot_p.right,
				Screen.y + Pivot_p.bottom);
			::D2D1_RECT_F srcArea = FocusRight;

			renderer.GetRenderTarget()->DrawBitmap(Adol, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			FocusRight = { 1, 425, 32, 476 };
		}
		else if (bUp)
		{
			FocusTop.left = FocusTop.left + AdolRatio.x*PlayerFocus.top;
			FocusTop.right = FocusTop.right + AdolRatio.x*PlayerFocus.top;

			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Screen.x + Pivot_p.left,
				Screen.y + Pivot_p.top,
				Screen.x + Pivot_p.right,
				Screen.y + Pivot_p.bottom);
			::D2D1_RECT_F srcArea = FocusTop;

			renderer.GetRenderTarget()->DrawBitmap(Adol, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			FocusTop = { 1, 531, 32, 582 };
		}
		else if (bDown)
		{
			FocusBottom.left = FocusBottom.left + AdolRatio.x*PlayerFocus.bottom;
			FocusBottom.right = FocusBottom.right + AdolRatio.x*PlayerFocus.bottom;

			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				Screen.x + Pivot_p.left,
				Screen.y + Pivot_p.top,
				Screen.x + Pivot_p.right,
				Screen.y + Pivot_p.bottom);
			::D2D1_RECT_F srcArea = FocusBottom;

			renderer.GetRenderTarget()->DrawBitmap(Adol, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);

			FocusBottom = { 1, 743, 32, 794 };
		}

	}
}

void cPlayer::PlayerHpRender(cD2DRenderer& renderer)
{

	WCHAR str[128];
	wsprintf(str, L"0,1,2,3 = %d, %d, %d, %d", CrushOn, State[0], State[1],delta);
	UINT32 cTextLength_c = (UINT32)wcslen(str);

	D2D1_RECT_F layoutRectc = D2D1::RectF(830, 150, 1130, 250);

	renderer.GetRenderTarget()->DrawTextW(
		str,
		cTextLength_c,
		renderer.GetTextFormat(),
		layoutRectc,
		renderer.GetBrush());


	if (PlayerHpBar != nullptr);
	{
		::D2D1_RECT_F dxArea = ::D2D1::RectF(
			239,
			507,
			239 + (3.73*PlayerHp),
			523);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 135, 12);
		renderer.GetRenderTarget()->DrawBitmap(PlayerHpBar, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
}

void cPlayer::LoadImages(cD2DRenderer& renderer, HWND hWnd)
{
	Adol = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Player/Adol.png");
	PlayerHpBar = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Player/HpBar.png");
	PlayerEffect = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Player/PlayerEffect.png");
	::InvalidateRect(hWnd, NULL, TRUE);
}

