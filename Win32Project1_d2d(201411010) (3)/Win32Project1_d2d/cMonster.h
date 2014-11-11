#pragma once
#include "cD2DRenderer.h"

class cMonster
{
protected:

	ID2D1Bitmap* Monster;
	ID2D1Bitmap* MonsterHpBar;
	ID2D1Bitmap* EmptyHpBar;
	ID2D1Bitmap* MonsterEffect;

	D2D1_RECT_F EffectPivot_m;

	D2D1_RECT_F MonsterEffect1;
	D2D1_RECT_F MonsterEffect2;
	D2D1_RECT_F MonsterEffect3;
	D2D1_RECT_F MonsterEffect4;
	D2D1_RECT_F MonsterEffect5;
	D2D1_RECT_F MonsterEffect6;
	D2D1_RECT_F MonsterEffect7;
	D2D1_RECT_F MonsterEffect8;
	D2D1_RECT_F MonsterEffect9;
	D2D1_RECT_F MonsterEffect10;

	BOOL SightX;
	BOOL SightY;

	POINT MonsterRange;

	float MonsterHp;

	float MonsterSpeed;

	int MonsterTileTypeL;
	int MonsterTileTypeR;
	int MonsterTileTypeU;
	int MonsterTileTypeD;

	float MonsterAttack;

	int MonsterWayRand;

	int MonsterCrushOn;

	double Dis;
	int X;
	int Y;
	float vectorx;
	float vectory;

	D2D1_RECT_F MonsterIdle;

	int Delta_E;

public:
	cMonster();
	~cMonster();
	int delta;
	POINT MonsterPos;

	void Update();
	void MonsterMove();
	void Render(cD2DRenderer& renderer);
	void EffectRender(cD2DRenderer& renderer);
	void EffectRect(D2D1_RECT_F &RT, int x, int y);

	void MonsterHpRender(cD2DRenderer& renderer);
	void LoadImages(cD2DRenderer& renderer, HWND hWnd);
	void RandomMove(int x, int y, int z);
	

	void Temp(int x, int y);

	int GetCrushOn_t(int a);
};

