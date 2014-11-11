#pragma once
#include "cGameManager.h"
class cInterFace
{
private:
	ID2D1Bitmap* Edge;
	ID2D1Bitmap* MenuBarMain;
	ID2D1Bitmap* MenuBar_Load;
	ID2D1Bitmap* MenuBar_Save;
	ID2D1Bitmap* MenuBar_Equip;
	ID2D1Bitmap* MenuBar_Inven;
	ID2D1Bitmap* MenuBar_Status;
	ID2D1Bitmap* MenuBar_Option;
	ID2D1Bitmap* EmptyHpBar;

	D2D1_RECT_F MenuBar0;
	D2D1_RECT_F MenuBar1;
	D2D1_RECT_F MenuBar2;
	D2D1_RECT_F MenuBar3;
	D2D1_RECT_F MenuBar4;
	D2D1_RECT_F MenuBar5;
	D2D1_RECT_F MenuBar6;
	D2D1_RECT_F MenuBar7;

	int MenuBarView;
	int MenuBar;
	float delta;

public:
	cInterFace();
	~cInterFace();
	void Update();
	void Render(cD2DRenderer& renderer);
	void MenuBarRender(cD2DRenderer& renderer);
	void LoadImages(cD2DRenderer& renderer, HWND hWnd);
};

