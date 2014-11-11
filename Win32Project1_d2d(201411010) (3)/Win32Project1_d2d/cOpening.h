#pragma once
#include "cGameManager.h"
class cOpening
{
private:

	ID2D1Bitmap* Opening;
	ID2D1Bitmap* Opening_Box;
	ID2D1Bitmap* GameStart_Line;
	ID2D1Bitmap* Exit_Line;



public:
	cOpening();
	~cOpening();

	int MouseOn;

	void Update();
	void Render(cD2DRenderer& renderer);
	void LoadImages(cD2DRenderer& renderer, HWND hWnd);

};

