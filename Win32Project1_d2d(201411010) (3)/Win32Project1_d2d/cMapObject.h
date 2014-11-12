#pragma once
#include "cGameManager.h"
class cMapObject
{

	ID2D1Bitmap*	TileLine;
	ID2D1Bitmap*	WoodenBuilding_s;
	ID2D1Bitmap*	WoodenBuilding_b;
	ID2D1Bitmap*	StoneBuilding_s;
	ID2D1Bitmap*	StoneBuilding_b;
	ID2D1Bitmap*	Fence;

	D2D1_RECT_F rWoodenBuilding_s;
	D2D1_RECT_F rWoodenBuilding_b;
	D2D1_RECT_F rStoneBuilding_s;
	D2D1_RECT_F rStoneBuilding_b;
	D2D1_RECT_F rFence;

	int x = 0;

public:
	cMapObject();
	~cMapObject();

	void Update();
	void Render(cD2DRenderer& renderer);
	void FrontBuildingRender(cD2DRenderer& renderer);
	void BackBuildingRender(cD2DRenderer& renderer);
	void LoadImages(cD2DRenderer& renderer, HWND hWnd);

	void Build(cD2DRenderer& renderer, ID2D1Bitmap* A, D2D1_RECT_F &RT, int posx, int posy);

	void DataRender(cD2DRenderer& renderer);
};