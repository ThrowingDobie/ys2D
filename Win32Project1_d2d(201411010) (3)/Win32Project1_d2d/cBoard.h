#pragma once

#include "cGameManager.h"
#include "cD2DRenderer.h"

class cBoard
{
private:

	ID2D1Bitmap*	TownTile;

	POINT Tile;


public:
	cBoard();
	~cBoard();

	void Update();
	void Render(cD2DRenderer& renderer);
	void LoadImages(cD2DRenderer& renderer, HWND hWnd);
	void TileSave();
	void TileLoad();
};

