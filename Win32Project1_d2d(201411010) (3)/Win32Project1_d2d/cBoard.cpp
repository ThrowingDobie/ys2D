#include "stdafx.h"
#include "cBoard.h"
#include "cD2DRenderer.h"

#include <cstdio>


cBoard::cBoard()
{
	Tile = { 0, 0 };
	TownTile = nullptr;
}


cBoard::~cBoard()
{
	SafeRelease(TownTile);
}

void cBoard::TileSave()
{
	FILE* pfile = nullptr;
	pfile = fopen("Tile.txt", "w");

	for (Tile.y = 0; Tile.y < (StageA_Size.y / TileSize.y); Tile.y++)
	{
		for (Tile.x = 0; Tile.x < (StageA_Size.x / TileSize.x); Tile.x++)
		{
			fprintf(pfile, "%d", MainTile[Tile.x][Tile.y]);
		}
		fprintf(pfile, "\n");
	}

	fclose(pfile);
}


void cBoard::TileLoad()
{
	char TileData = 0;

	FILE* pfile = nullptr;
	pfile = fopen("Tile.txt", "r+");

	if (pfile != nullptr)
	{
		for (Tile.y = 0; Tile.y <= (StageA_Size.y / TileSize.y); Tile.y++)
		{
			for (Tile.x = 0; Tile.x <= (StageA_Size.x / TileSize.x); Tile.x++)
			{
				TileData = fgetc(pfile);
				if (TileData != '\n')
				{
					MainTile[Tile.x][Tile.y] = TileData - 48;
				}
			}
		}
		fclose(pfile);
	}


}

void cBoard::Render(cD2DRenderer& renderer)
{
	//float a, b = 0;
	//
	//for (b = g_Camera.y / TileSize.y; b <= ((g_Camera.y + Resolution.y) / TileSize.y); b++)
	//{
	//	for (a = g_Camera.x / TileSize.x; a <= ((g_Camera.x + Resolution.x) / TileSize.x); a++)
	//	{
	//		if (TownTile != nullptr)
	//		{
	//			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
	//			::D2D1_RECT_F dxArea = ::D2D1::RectF(a*TileSize.x, b*TileSize.y,
	//				a*TileSize.x + TileSize.x, b*TileSize.y + TileSize.y);
	//			::D2D1_RECT_F srcArea = ::D2D1::RectF(a*TileSize.x, b*TileSize.y,
	//				a*TileSize.x + TileSize.x, b*TileSize.y + TileSize.y);

	//			renderer.GetRenderTarget()->DrawBitmap(TownTile, dxArea, 1.0f,
	//				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
	//				srcArea);
	//		}
	//	}
	//}

	g_Camera.x = PlayerPos.x - (Resolution.x/2);
	g_Camera.y = PlayerPos.y - (Resolution.y/2)+65;

	if (g_Camera.x < 0) g_Camera.x = 0;
	if (g_Camera.y < 0) g_Camera.y = 0;
	if (g_Camera.x > StageA_Size.x-Resolution.x) g_Camera.x = StageA_Size.x-Resolution.x;
	if (g_Camera.y > StageA_Size.y - Resolution.y + 150) g_Camera.y = StageA_Size.y - Resolution.y + 150;
	
	if (TownTile != nullptr)
	{
		D2D1_SIZE_U size = renderer.GetRenderTargetSize();
		::D2D1_RECT_F dxArea = ::D2D1::RectF(28, 28, Resolution.x-21, Resolution.y-21);		//¸ð´ÏÅÍ
		::D2D1_RECT_F srcArea = ::D2D1::RectF(g_Camera.x, g_Camera.y,
			g_Camera.x + Resolution.x, g_Camera.y + Resolution.y);

		renderer.GetRenderTarget()->DrawBitmap(TownTile, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
}

void cBoard::LoadImages(cD2DRenderer& renderer, HWND hWnd)
{
	TownTile = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Map/TownA.png");
	::InvalidateRect(hWnd, NULL, TRUE);
}