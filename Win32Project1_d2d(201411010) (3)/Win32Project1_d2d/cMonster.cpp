#include "stdafx.h"
#include "cMonster.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>


cMonster::cMonster()
{
	Monster = nullptr;
	MonsterHpBar = nullptr;
	EmptyHpBar = nullptr;
	MonsterEffect = nullptr;
	//MonsterPos.x = 0;
	//MonsterPos.y = 0;
	MonsterSpeed = 5;
	MonsterHp = 100;
	MonsterAttack = 1.0f;

	EffectRect(MonsterEffect1, 74, 976);
	EffectRect(MonsterEffect2, 202, 976);
	EffectRect(MonsterEffect3, 330, 976);
	EffectRect(MonsterEffect4, 459, 976);
	EffectRect(MonsterEffect5, 585, 976);
	EffectRect(MonsterEffect6, 713, 976);
	EffectRect(MonsterEffect7, 842, 976);
	EffectRect(MonsterEffect8, 971, 976);
	EffectRect(MonsterEffect9, 1100, 976);
	EffectRect(MonsterEffect10, 1228, 976);

}

cMonster::~cMonster()
{
	SafeRelease(Monster);
	SafeRelease(MonsterHpBar);
	SafeRelease(EmptyHpBar);
	SafeRelease(MonsterEffect);
}

void cMonster::Temp(int x, int y)
{
	MonsterPos.x = x;
	MonsterPos.y = y;
}

void cMonster::RandomMove(int x, int y, int z)
{
	int result = (rand() % 100) + 1;
	if (result >= x && result <= y)
	{
		MonsterWayRand = z;
	}
}

void cMonster::Update()
{

	if (MonsterPos.x >= g_Camera.x && MonsterPos.x <= g_Camera.x + Resolution.x) SightX = true;
	else SightX = false;
	if (MonsterPos.y >= g_Camera.y && MonsterPos.y <= g_Camera.y + Resolution.y) SightY = true;
	else SightY = false;

	if (SightX && SightY)
	{
		if (MonsterHp > 0)
		{
			MonsterTileTypeL = MainTile[((MonsterPos.x - 10) / TileSize.x)][(MonsterPos.y) / TileSize.y];
			MonsterTileTypeR = MainTile[((MonsterPos.x + 10) / TileSize.x)][(MonsterPos.y) / TileSize.y];
			MonsterTileTypeU = MainTile[((MonsterPos.x) / TileSize.x)][(MonsterPos.y - 10) / TileSize.y];
			MonsterTileTypeD = MainTile[((MonsterPos.x) / TileSize.x)][(MonsterPos.y + 10) / TileSize.y];

			srand(time(NULL));
			MonsterWayRand = rand()*rand() % 5;
			//MonsterWayRand = 0;

			Dis = sqrt((MonsterPos.x - PlayerPos.x)*(MonsterPos.x - PlayerPos.x) +
				(MonsterPos.y - PlayerPos.y)*(MonsterPos.y - PlayerPos.y));

			X = PlayerPos.x - MonsterPos.x; // 플레이어와 몬스터 상대적 위치
			Y = PlayerPos.y - MonsterPos.y; // 플레이어와 몬스터 상대적 위치

			vectorx = X / Dis;
			vectory = Y / Dis;

			if (X >= -3 && X <= 3) MonsterRange.x = 1;
			else MonsterRange.x = 0;
			if (Y >= -3 && Y <= 3) MonsterRange.y = 1;
			else MonsterRange.y = 0;
		}
	}

	else
	{
		MonsterTileTypeL = 0;
		MonsterTileTypeR = 0;
		MonsterTileTypeU = 0;
		MonsterTileTypeD = 0;
	}
	
	delta++;
	if (delta > 100) delta = 0;

	if (MonsterHp <= 0)
	{
		MonsterCrushOn = 0;
		MonsterTile = { 0, 0, 0, 0 };
		if (delta == 99)
		{
			MonsterHp = 100;
			//MonsterPos = { 1100, 1200 };
		}
	}

	if (MonsterCrushOn == 1)
	{
		Delta_E += 1;
		if (Delta_E > 13) Delta_E = 0;
	}
	else Delta_E = 0;

}


int cMonster::GetCrushOn_t(int a)
{
	if (SightX && SightY)
	{
		return MonsterCrushOn;
	}

}

void cMonster::EffectRect(D2D1_RECT_F &RT, int x, int y)
{
	RT.left = x - 70;
	RT.right = x + 70;
	RT.top = y - 70;
	RT.bottom = y + 70;
}

void cMonster::EffectRender(cD2DRenderer& renderer)
{
	EffectPivot_m;
	EffectPivot_m = { MonsterPos.x - 30, MonsterPos.y - 50, MonsterPos.x + 30, MonsterPos.y };
	if (MonsterCrushOn == 1)
	{
		if (Delta_E == 0)
		{
			if (MonsterEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_m.left,
					Screen.y + EffectPivot_m.top,
					Screen.x + EffectPivot_m.right,
					Screen.y + EffectPivot_m.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					MonsterEffect1.left,
					MonsterEffect1.top,
					MonsterEffect1.right,
					MonsterEffect1.bottom);
				renderer.GetRenderTarget()->DrawBitmap(MonsterEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (Delta_E == 1)
		{
			if (MonsterEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_m.left,
					Screen.y + EffectPivot_m.top,
					Screen.x + EffectPivot_m.right,
					Screen.y + EffectPivot_m.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					MonsterEffect2.left,
					MonsterEffect2.top,
					MonsterEffect2.right,
					MonsterEffect2.bottom);
				renderer.GetRenderTarget()->DrawBitmap(MonsterEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (Delta_E == 2)
		{
			if (MonsterEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_m.left,
					Screen.y + EffectPivot_m.top,
					Screen.x + EffectPivot_m.right,
					Screen.y + EffectPivot_m.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					MonsterEffect3.left,
					MonsterEffect3.top,
					MonsterEffect3.right,
					MonsterEffect3.bottom);
				renderer.GetRenderTarget()->DrawBitmap(MonsterEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (Delta_E == 3)
		{
			if (MonsterEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_m.left,
					Screen.y + EffectPivot_m.top,
					Screen.x + EffectPivot_m.right,
					Screen.y + EffectPivot_m.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					MonsterEffect4.left,
					MonsterEffect4.top,
					MonsterEffect4.right,
					MonsterEffect4.bottom);
				renderer.GetRenderTarget()->DrawBitmap(MonsterEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (Delta_E == 4)
		{
			if (MonsterEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_m.left,
					Screen.y + EffectPivot_m.top,
					Screen.x + EffectPivot_m.right,
					Screen.y + EffectPivot_m.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					MonsterEffect5.left,
					MonsterEffect5.top,
					MonsterEffect5.right,
					MonsterEffect5.bottom);
				renderer.GetRenderTarget()->DrawBitmap(MonsterEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (Delta_E == 5)
		{
			if (MonsterEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_m.left,
					Screen.y + EffectPivot_m.top,
					Screen.x + EffectPivot_m.right,
					Screen.y + EffectPivot_m.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					MonsterEffect6.left,
					MonsterEffect6.top,
					MonsterEffect6.right,
					MonsterEffect6.bottom);
				renderer.GetRenderTarget()->DrawBitmap(MonsterEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (Delta_E == 6)
		{
			if (MonsterEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_m.left,
					Screen.y + EffectPivot_m.top,
					Screen.x + EffectPivot_m.right,
					Screen.y + EffectPivot_m.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					MonsterEffect7.left,
					MonsterEffect7.top,
					MonsterEffect7.right,
					MonsterEffect7.bottom);
				renderer.GetRenderTarget()->DrawBitmap(MonsterEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (Delta_E == 7)
		{
			if (MonsterEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_m.left,
					Screen.y + EffectPivot_m.top,
					Screen.x + EffectPivot_m.right,
					Screen.y + EffectPivot_m.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					MonsterEffect8.left,
					MonsterEffect8.top,
					MonsterEffect8.right,
					MonsterEffect8.bottom);
				renderer.GetRenderTarget()->DrawBitmap(MonsterEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (Delta_E == 8)
		{
			if (MonsterEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_m.left,
					Screen.y + EffectPivot_m.top,
					Screen.x + EffectPivot_m.right,
					Screen.y + EffectPivot_m.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					MonsterEffect9.left,
					MonsterEffect9.top,
					MonsterEffect9.right,
					MonsterEffect9.bottom);
				renderer.GetRenderTarget()->DrawBitmap(MonsterEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		if (Delta_E == 9)
		{
			if (MonsterEffect != nullptr);
			{
				D2D1_SIZE_U size = renderer.GetRenderTargetSize();
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + EffectPivot_m.left,
					Screen.y + EffectPivot_m.top,
					Screen.x + EffectPivot_m.right,
					Screen.y + EffectPivot_m.bottom);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(
					MonsterEffect10.left,
					MonsterEffect10.top,
					MonsterEffect10.right,
					MonsterEffect10.bottom);
				renderer.GetRenderTarget()->DrawBitmap(MonsterEffect, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
	}


}

void cMonster::MonsterMove()
{
	MonsterAttack = 2;

	if (SightX && SightY)
	{
		if (MonsterHp > 0)
		{
			//if (delta == 1)
			{
				if (Dis <= 29)
				{
					if (bLeft == false && bRight == false && bUp == false && bDown == false)
					{
						MonsterCrushOn = 2;
						PlayerHp -= (MonsterAttack-PlayerDefense);
						if (X == 0 && Y > 0)
						{
							if (TileTypeD == 0) PlayerPos.y += 2;
						}
						else if (X == 0 && Y < 0)
						{
							if (TileTypeU == 0) PlayerPos.y -= 2;
						}
						else if (X > 0 && Y == 0)
						{
							if (TileTypeR == 0) PlayerPos.x += 2;
						}
						else if (X < 0 && Y == 0)
						{
							if (TileTypeL == 0) PlayerPos.x -= 2;
						}

						if (X > 0 && Y > 0)
						{
							if (TileTypeR == 0) PlayerPos.x += 2;
							if (TileTypeD == 0) PlayerPos.y += 2;
						}
						else if (X < 0 && Y >0)
						{
							if (TileTypeL == 0) PlayerPos.x -= 2;
							if (TileTypeD == 0) PlayerPos.y += 2;
						}
						else if (X > 0 && Y < 0)
						{
							if (TileTypeR == 0) PlayerPos.x += 2;
							if (TileTypeU == 0) PlayerPos.y -= 2;
						}
						else if (X < 0 && Y < 0)
						{
							if (TileTypeL == 0) PlayerPos.x -= 2;
							if (TileTypeU == 0) PlayerPos.y -= 2;
						}
						if (PlayerHp < 0) PlayerHp = 100;
					}
					else
					{
						MonsterHp -= PlayerAttack;
						if (X > 0 && bLeft == true)
						{
							MonsterCrushOn = 1;
							//MonsterHp--;
							if (MonsterTileTypeL)
							{
								Temp(MonsterPos.x, MonsterPos.y);
								MonsterTile.left = 1;
							}
							else
							{
								Temp(MonsterPos.x - MonsterSpeed, MonsterPos.y);
								MonsterTile.left = 0;
							}
						}
						else
							if (X < 0 && bRight == true)
							{
							MonsterCrushOn = 1;

							//MonsterHp--;
							if (MonsterTileTypeR)
							{
								Temp(MonsterPos.x, MonsterPos.y);
								MonsterTile.right = 1;
							}

							else
							{
								Temp(MonsterPos.x + MonsterSpeed, MonsterPos.y);
								MonsterTile.right = 0;
							}
							}
						if (Y > 0 && bUp == true)
						{
							MonsterCrushOn = 1;
							//MonsterHp--;
							if (MonsterTileTypeU)
							{
								Temp(MonsterPos.x, MonsterPos.y);
								MonsterTile.top = 1;
							}
							else
							{
								Temp(MonsterPos.x, MonsterPos.y - MonsterSpeed);
								MonsterTile.top = 0;
							}
						}
						if (Y < 0 && bDown == true)
						{
							MonsterCrushOn = 1;
							//MonsterHp--;
							if (MonsterTileTypeD)
							{
								Temp(MonsterPos.x, MonsterPos.y);
								MonsterTile.bottom = 1;
							}

							else
							{
								Temp(MonsterPos.x, MonsterPos.y + MonsterSpeed);
								MonsterTile.bottom = 0;
							}
						}
					}
					
				}

				if (Dis < 200 && Dis > 29)
				{
					MonsterCrushOn = 0;

					if (MonsterTileTypeR) Temp(MonsterPos.x, MonsterPos.y);
					else if (X > 0)
					{
						//if (MonsterRange.x) Temp(MonsterPos.x + MonsterSpeed, MonsterPos.y);
						Temp(MonsterPos.x + MonsterSpeed, MonsterPos.y);
					}

					if (MonsterTileTypeL) Temp(MonsterPos.x, MonsterPos.y);
					else if (X < 0)Temp(MonsterPos.x - MonsterSpeed, MonsterPos.y);
					if (MonsterTileTypeD) Temp(MonsterPos.x, MonsterPos.y);
					else if (Y > 0) Temp(MonsterPos.x, MonsterPos.y + MonsterSpeed);
					if (MonsterTileTypeU) Temp(MonsterPos.x, MonsterPos.y);
					else if (Y < 0) Temp(MonsterPos.x, MonsterPos.y - MonsterSpeed);

				}

				if (Dis > 200)
				{
					MonsterCrushOn = 0;
					if (MonsterWayRand == 0)
					{
						if (MonsterTileTypeL) Temp(MonsterPos.x, MonsterPos.y);
						else Temp(MonsterPos.x - MonsterSpeed, MonsterPos.y);
						//PlayerFocus.left++;
						//if (PlayerFocus.left == 4) PlayerFocus.left = 1;
						//PlayerWay = 1;
					}
					if (MonsterWayRand == 1)
					{
						if (MonsterTileTypeR) Temp(MonsterPos.x, MonsterPos.y);
						else Temp(MonsterPos.x + MonsterSpeed, MonsterPos.y);
						//PlayerFocus.right++;
						//if (PlayerFocus.right == 4) PlayerFocus.right = 1;
						//PlayerWay = 2;
					}
					if (MonsterWayRand == 2)
					{
						if (MonsterTileTypeU) Temp(MonsterPos.x, MonsterPos.y);
						else Temp(MonsterPos.x, MonsterPos.y - MonsterSpeed);
						//PlayerFocus.top++;
						//if (PlayerFocus.top == 4) PlayerFocus.top = 1;
						//PlayerWay = 3;
					}
					if (MonsterWayRand == 3)
					{
						if (MonsterTileTypeD) Temp(MonsterPos.x, MonsterPos.y);
						else Temp(MonsterPos.x, MonsterPos.y + MonsterSpeed);
						//PlayerFocus.bottom++;
						//if (PlayerFocus.bottom == 4) PlayerFocus.bottom = 1;
						//PlayerWay = 4;
					}
				}
			}
		}
	}
	
	
}
void cMonster::Render(cD2DRenderer& renderer)
{
	if (SightX && SightY)
	{
		if (MonsterHp > 0)
		{
			if (Monster != nullptr);
			{
				::D2D1_RECT_F dxArea = ::D2D1::RectF(
					Screen.x + MonsterPos.x - 16,
					Screen.y + MonsterPos.y - 52,
					Screen.x + MonsterPos.x + 16,
					Screen.y + MonsterPos.y);
				::D2D1_RECT_F srcArea = ::D2D1::RectF(310, 103, 375, 198);
				renderer.GetRenderTarget()->DrawBitmap(Monster, dxArea, 1.0f,
					D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
					srcArea);
			}
		}
		//else Monster = nullptr;
	}


	WCHAR str[128];
	wsprintf(str, L"MonsterCrushOn = %d, %d", MonsterCrushOn, Delta_E);
	UINT32 cTextLength_c = (UINT32)wcslen(str);

	D2D1_RECT_F layoutRectc = D2D1::RectF(830, 200, 1130, 250);

	renderer.GetRenderTarget()->DrawTextW(
		str,
		cTextLength_c,
		renderer.GetTextFormat(),
		layoutRectc,
		renderer.GetBrush());

}
void cMonster::MonsterHpRender(cD2DRenderer& renderer)
{
	if (SightX && SightY)
	{
		if (MonsterHp > 0)
		{
			if (Dis < 200)
			{
				if (MonsterHpBar != nullptr);
				{
					D2D1_SIZE_U size = renderer.GetRenderTargetSize();
					::D2D1_RECT_F dxArea = ::D2D1::RectF(
						239,
						537,
						239 + (3.73*MonsterHp),
						553);
					::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 135, 12);
					renderer.GetRenderTarget()->DrawBitmap(MonsterHpBar, dxArea, 1.0f,
						D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
						srcArea);
				}
			}
		}
	}
}
void cMonster::LoadImages(cD2DRenderer& renderer, HWND hWnd)
{
	Monster = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Monster/Monster.png");
	MonsterHpBar = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Monster/HpBar.png");
	EmptyHpBar = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Monster/EmptyHpBar.png");
	MonsterEffect = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Monster/MonsterEffect.png");
}
