#pragma once
#include "cGameManager.h"

class cPlayer 
{
private:
	RECT PlayerFocus;

	D2D1_RECT_F FocusLeft;
	D2D1_RECT_F FocusRight;
	D2D1_RECT_F FocusTop;
	D2D1_RECT_F FocusBottom;

	D2D1_RECT_F Focus1;
	D2D1_RECT_F Focus3;
	D2D1_RECT_F Focus7;
	D2D1_RECT_F Focus9;

	D2D1_RECT_F WayLeft;
	D2D1_RECT_F WayRight;
	D2D1_RECT_F WayTop;
	D2D1_RECT_F WayBottom;

	D2D1_RECT_F Way1;
	D2D1_RECT_F Way3;
	D2D1_RECT_F Way7;
	D2D1_RECT_F Way9;

	D2D1_RECT_F PlayerEffect1;
	D2D1_RECT_F PlayerEffect2;
	D2D1_RECT_F PlayerEffect3;
	D2D1_RECT_F PlayerEffect4;
	D2D1_RECT_F PlayerEffect5;
	D2D1_RECT_F PlayerEffect6;
	D2D1_RECT_F PlayerEffect7;

	POINTF AdolRatio;

	int PlayerWay;
	int CrushOn;
	int State[10];
	int FirstCrush;

	ID2D1Bitmap* PlayerEffect;

	int delta;

public:
	cPlayer();
	~cPlayer();

	ID2D1Bitmap* Adol;
	ID2D1Bitmap* PlayerHpBar;

	void KeyDown(DWORD dwKey);
	void KeyUp(DWORD dwKey);
	void Update();
	void PlayerMove();
	void Render(cD2DRenderer& renderer);
	void EffectRender(cD2DRenderer& renderer);
	void PlayerHpRender(cD2DRenderer& renderer);
	void LoadImages(cD2DRenderer& renderer, HWND hWnd);

	void Temp(int x, int y);
	void EffectRect(D2D1_RECT_F &RT, int x, int y);
};

