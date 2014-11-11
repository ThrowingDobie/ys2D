#pragma once
#include "cGameManager.h"

class cEquip
{
private:
	ID2D1Bitmap* EquipMain;
	ID2D1Bitmap* EquipSelectingLine;
	ID2D1Bitmap* EquipSelectedLine;
	ID2D1Bitmap* ReturnLine;
	ID2D1Bitmap* ShortSword_imf;
	ID2D1Bitmap* SmallShield_imf;
	ID2D1Bitmap* ChainMail_imf;
	ID2D1Bitmap* PowerRing_imf;
	ID2D1Bitmap* ValueBar;
	ID2D1Bitmap* StrDef;

	//int MouseOn = 0;

	D2D1_RECT_F ReturnPos;
	D2D1_RECT_F Sword_1_Pos;
	D2D1_RECT_F Shield_1_Pos;
	D2D1_RECT_F Armor_1_Pos;
	D2D1_RECT_F Ring_1_Pos;
	D2D1_RECT_F Sword_1_Pos_1;
	D2D1_RECT_F Shield_1_Pos_1;
	D2D1_RECT_F Armor_1_Pos_1;
	D2D1_RECT_F Ring_1_Pos_1;
	
	int MouseOn;
	int MouseOnA[5][5];
	int EquipSelect[5][5];

	float Weapon;
	float Shield;
	float Armor;
	float Ring;

public:
	cEquip();
	~cEquip();

	void Update();
	void RenderUpdate();
	void Render(cD2DRenderer& renderer);
	void LoadImages(cD2DRenderer& renderer, HWND hWnd);
	int MousePOINT(D2D1_RECT_F &RT, int x, BOOL Click);
};

