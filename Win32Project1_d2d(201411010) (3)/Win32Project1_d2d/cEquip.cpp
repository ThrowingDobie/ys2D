#include "stdafx.h"
#include "cEquip.h"


cEquip::cEquip()
{
	EquipMain = nullptr;
	EquipSelectingLine = nullptr;
	EquipSelectedLine = nullptr;
	ReturnLine = nullptr;
	ShortSword_imf = nullptr;
	SmallShield_imf = nullptr;
	ChainMail_imf = nullptr;
	PowerRing_imf = nullptr;
	ValueBar = nullptr;
	StrDef = nullptr;

	ReturnPos = { 264.0f, 392.0f, 380.0f, 425.0f };
	Sword_1_Pos = { 133, 154, 177, 198 };
	Shield_1_Pos = { 133, 209, 177, 253 };
	Armor_1_Pos = { 133, 264, 177, 308 };
	Ring_1_Pos = { 133, 319, 177, 363 };
	Sword_1_Pos_1 = { 133, 154, 177, 198 + 3 }; 
	Shield_1_Pos_1 = { 133, 209, 177, 253 + 3 };
	Armor_1_Pos_1 = { 133, 264, 177, 308 + 3 };
	Ring_1_Pos_1 = { 133, 319, 177, 363 + 3 };
}


cEquip::~cEquip()
{
	SafeRelease(EquipMain);
	SafeRelease(EquipSelectingLine);
	SafeRelease(EquipSelectedLine);
	SafeRelease(ReturnLine);
	SafeRelease(ShortSword_imf);
	SafeRelease(SmallShield_imf);
	SafeRelease(ChainMail_imf);
	SafeRelease(PowerRing_imf);
	SafeRelease(ValueBar);
	SafeRelease(StrDef);
}

int cEquip::MousePOINT(D2D1_RECT_F &RT, int x, BOOL Click)
{
	POINT pos;

	if (Click == 0) pos = MouseMove;
	else if (Click == 1) pos = MouseLD;
	else if (Click == 2) pos = MouseRD;


	if (pos.x >= RT.left &&
		pos.x <= RT.right &&
		pos.y >= RT.top &&
		pos.y <= RT.bottom)
	{
		MouseMove = { 0, 0 };
		MouseLD = { 0, 0 };
		MouseRD = { 0, 0 };
		MouseState = { 0, 0 };
		return x;
	}
	else return 0;

}

void cEquip::RenderUpdate()
{
	// 되돌아감
	if (MouseMove.x >= ReturnPos.left &&
		MouseMove.x <= ReturnPos.right &&
		MouseMove.y >= ReturnPos.top &&
		MouseMove.y <= ReturnPos.bottom)
	{
		MouseOn = 1;
	}
	else MouseOn = 0;

	if (MouseLD.x >= ReturnPos.left &&
		MouseLD.x <= ReturnPos.right &&
		MouseLD.y >= ReturnPos.top &&
		MouseLD.y <= ReturnPos.bottom)
	{
		MouseOn = 99;
	}

	if (MouseOn == 99)
	{
		Stage = 1;
		MouseMove = { 0, 0 };
		MouseLD = { 0, 0 };
		MouseRD = { 0, 0 };
		MouseState = { 0, 0 };
	}

	// 장비선택중
	if (MouseMove.x >= Sword_1_Pos.left &&
		MouseMove.x <= Sword_1_Pos.right &&
		MouseMove.y >= Sword_1_Pos.top &&
		MouseMove.y <= Sword_1_Pos.bottom)
	{
		MouseOnA[1][1] = 1;
	}
	else MouseOnA[1][1] = 0;
	if (MouseMove.x >= Shield_1_Pos.left &&
		MouseMove.x <= Shield_1_Pos.right &&
		MouseMove.y >= Shield_1_Pos.top &&
		MouseMove.y <= Shield_1_Pos.bottom)
	{
		MouseOnA[2][1] = 1;
	}
	else MouseOnA[2][1] = 0;
	if (MouseMove.x >= Armor_1_Pos.left &&
		MouseMove.x <= Armor_1_Pos.right &&
		MouseMove.y >= Armor_1_Pos.top &&
		MouseMove.y <= Armor_1_Pos.bottom)
	{
		MouseOnA[3][1] = 1;
	}
	else MouseOnA[3][1] = 0;
	if (MouseMove.x >= Ring_1_Pos.left &&
		MouseMove.x <= Ring_1_Pos.right &&
		MouseMove.y >= Ring_1_Pos.top &&
		MouseMove.y <= Ring_1_Pos.bottom)
	{
		MouseOnA[4][1] = 1;
	}
	else MouseOnA[4][1] = 0;


	// 장비선택됨
	if (EquipSelect[1][1] == 0) EquipSelect[1][1] = MousePOINT(Sword_1_Pos, 1, 1);
	if (EquipSelect[2][1] == 0) EquipSelect[2][1] = MousePOINT(Shield_1_Pos, 1, 1);
	if (EquipSelect[3][1] == 0) EquipSelect[3][1] = MousePOINT(Armor_1_Pos, 1, 1);
	if (EquipSelect[4][1] == 0) EquipSelect[4][1] = MousePOINT(Ring_1_Pos, 1, 1);


	// 장비해제
	if (MouseRD.x >= Sword_1_Pos.left &&
		MouseRD.x <= Sword_1_Pos.right &&
		MouseRD.y >= Sword_1_Pos.top &&
		MouseRD.y <= Sword_1_Pos.bottom && EquipSelect[1][1])
	{
		EquipSelect[1][1] = 0;
	}
	if (MouseRD.x >= Shield_1_Pos.left &&
		MouseRD.x <= Shield_1_Pos.right &&
		MouseRD.y >= Shield_1_Pos.top &&
		MouseRD.y <= Shield_1_Pos.bottom && EquipSelect[2][1])
	{
		EquipSelect[2][1] = 0;
	}
	if (MouseRD.x >= Armor_1_Pos.left &&
		MouseRD.x <= Armor_1_Pos.right &&
		MouseRD.y >= Armor_1_Pos.top &&
		MouseRD.y <= Armor_1_Pos.bottom && EquipSelect[3][1])
	{
		EquipSelect[3][1] = 0;
	}
	if (MouseRD.x >= Ring_1_Pos.left &&
		MouseRD.x <= Ring_1_Pos.right &&
		MouseRD.y >= Ring_1_Pos.top &&
		MouseRD.y <= Ring_1_Pos.bottom && EquipSelect[4][1])
	{
		EquipSelect[4][1] = 0;
	}
}

void cEquip::Update()
{
	if (EquipSelect[1][1]) Weapon = 1.9;
	else if (EquipSelect[1][1] == 0) Weapon = 1.0f;
	if (EquipSelect[2][1]) Shield = 1.0f;
	else if (EquipSelect[2][1] == 0) Shield = 0.1f;
	if (EquipSelect[3][1]) Armor = 0.9f;
	else if (EquipSelect[3][1] == 0) Armor = 0.1f;
	if (EquipSelect[4][1]) Ring = 1.5f;
	else if (EquipSelect[4][1] == 0) Ring = 1.0f;

	
	PlayerAttack = Weapon*Ring;
	PlayerDefense = Armor + Shield;


	//if (EquipSelect[3][1]) PlayerDefense = 1.1;


}

void cEquip::Render(cD2DRenderer& renderer)
{
	if (EquipMain != nullptr)
	{
		::D2D1_RECT_F dxArea = ::D2D1::RectF(0, 0, Resolution.x, Resolution.y);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 800, 600);
		renderer.GetRenderTarget()->DrawBitmap(EquipMain, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}



	if (MouseOn == 1)
	{
		if (ReturnLine != nullptr)
		{
			::D2D1_RECT_F dxArea = ReturnPos;
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 117, 34);
			renderer.GetRenderTarget()->DrawBitmap(ReturnLine, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}
	if (MouseOnA[1][1] == 1)
	{
		if (ShortSword_imf != nullptr)
		{
			::D2D1_RECT_F dxArea = {0,0,800,600};
			::D2D1_RECT_F srcArea = { 0, 0, 800, 600 };
			renderer.GetRenderTarget()->DrawBitmap(ShortSword_imf, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		if (EquipSelectingLine != nullptr)
		{
			::D2D1_RECT_F dxArea = Sword_1_Pos;
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 45, 45);
			renderer.GetRenderTarget()->DrawBitmap(EquipSelectingLine, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}
	if (MouseOnA[2][1] == 1)
	{
		if (SmallShield_imf != nullptr)
		{
			::D2D1_RECT_F dxArea = { 0, 0, 800, 600 };
			::D2D1_RECT_F srcArea = { 0, 0, 800, 600 };
			renderer.GetRenderTarget()->DrawBitmap(SmallShield_imf, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}

		if (EquipSelectingLine != nullptr)
		{
			::D2D1_RECT_F dxArea = Shield_1_Pos;
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 45, 45);
			renderer.GetRenderTarget()->DrawBitmap(EquipSelectingLine, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}
	if (MouseOnA[3][1] == 1)
	{
		if (ChainMail_imf != nullptr)
		{
			::D2D1_RECT_F dxArea = { 0, 0, 800, 600 };
			::D2D1_RECT_F srcArea = { 0, 0, 800, 600 };
			renderer.GetRenderTarget()->DrawBitmap(ChainMail_imf, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		if (EquipSelectingLine != nullptr)
		{
			::D2D1_RECT_F dxArea = Armor_1_Pos;
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 45, 45);
			renderer.GetRenderTarget()->DrawBitmap(EquipSelectingLine, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}
	if (MouseOnA[4][1] == 1)
	{
		if (PowerRing_imf != nullptr)
		{
			::D2D1_RECT_F dxArea = { 0, 0, 800, 600 };
			::D2D1_RECT_F srcArea = { 0, 0, 800, 600 };
			renderer.GetRenderTarget()->DrawBitmap(PowerRing_imf, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
		if (EquipSelectingLine != nullptr)
		{
			::D2D1_RECT_F dxArea = Ring_1_Pos;
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 45, 45);
			renderer.GetRenderTarget()->DrawBitmap(EquipSelectingLine, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}

	if (EquipSelect[1][1]==1)
	{
		if (EquipSelectedLine != nullptr)
		{
			::D2D1_RECT_F dxArea = Sword_1_Pos_1;
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 45, 48);
			renderer.GetRenderTarget()->DrawBitmap(EquipSelectedLine, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}
	if (EquipSelect[2][1]==1)
	{
		if (EquipSelectedLine != nullptr)
		{
			::D2D1_RECT_F dxArea = Shield_1_Pos_1;
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 45, 48);
			renderer.GetRenderTarget()->DrawBitmap(EquipSelectedLine, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}
	if (EquipSelect[3][1]==1)
	{
		if (EquipSelectedLine != nullptr)
		{
			::D2D1_RECT_F dxArea = Armor_1_Pos_1;
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 45, 48);
			renderer.GetRenderTarget()->DrawBitmap(EquipSelectedLine, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}
	if (EquipSelect[4][1]==1)
	{
		if (EquipSelectedLine != nullptr)
		{
			::D2D1_RECT_F dxArea = Ring_1_Pos_1;
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 45, 48);
			renderer.GetRenderTarget()->DrawBitmap(EquipSelectedLine, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}

	if (ValueBar != nullptr)
	{
		::D2D1_RECT_F dxArea = ::D2D1::RectF(182, 108, 182+1.81 * 25 * PlayerAttack, 115);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 8, 8);
		renderer.GetRenderTarget()->DrawBitmap(ValueBar, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	if (ValueBar != nullptr)
	{
		::D2D1_RECT_F dxArea = ::D2D1::RectF(182, 121, 182+1.81 * 25 * PlayerDefense, 128);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 8, 8);
		renderer.GetRenderTarget()->DrawBitmap(ValueBar, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	if (StrDef != nullptr)
	{
		::D2D1_RECT_F dxArea = ::D2D1::RectF(145, 106, 145 + 22, 107 + 23);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 24, 23);
		renderer.GetRenderTarget()->DrawBitmap(StrDef, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	WCHAR str[128];
	wsprintf(str, L"MouseOn = %d", EquipSelect[1][1]);
	UINT32 cTextLength_c = (UINT32)wcslen(str);

	D2D1_RECT_F layoutRectc = D2D1::RectF(830, 350, 1130, 400);

	renderer.GetRenderTarget()->DrawTextW(
		str,
		cTextLength_c,
		renderer.GetTextFormat(),
		layoutRectc,
		renderer.GetBrush());

}
void cEquip::LoadImages(cD2DRenderer& renderer, HWND hWnd)
{
	EquipMain = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Equip/EquipMain.png");
	EquipSelectingLine = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Equip/EquipSelectingLine.png");
	EquipSelectedLine = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Equip/EquipSelectedLine.png");
	ReturnLine = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Equip/ReturnLine.png");
	ShortSword_imf = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Equip/Equip_ShorSword_Imf.png");
	SmallShield_imf = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Equip/Equip_SmallShield_Imf.png");
	ChainMail_imf = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Equip/Equip_ChainMail_Imf.png");
	PowerRing_imf = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Equip/Equip_PowerRing_Imf.png");
	ValueBar = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Equip/ValueBar.png");
	StrDef = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Equip/StrDef.png");
}
