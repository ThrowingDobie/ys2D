#pragma once
#include "cGameManager.h"

class cInven
{
	ID2D1Bitmap* InvenMain;
	ID2D1Bitmap* Potion;
	ID2D1Bitmap* Potion_Select;
	ID2D1Bitmap* InvenSelectingLine;
	ID2D1Bitmap* InvenSelectedLine;
	ID2D1Bitmap* ReturnLine;

	D2D1_RECT_F Potion_Pos;
	D2D1_RECT_F ReturnPos;

	int MouseOn;
	int MouseOnR;
	int MouseOnP;

public:
	cInven();
	~cInven();

	void Update();
	void RenderUpdate();
	void Render(cD2DRenderer& renderer);
	void LoadImages(cD2DRenderer& renderer, HWND hWnd);
};

