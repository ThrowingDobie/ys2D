// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// Win32Project1_d2d.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"
#include "cGameManager.h"


// TODO: 필요한 추가 헤더는
// 이 파일이 아닌 STDAFX.H에서 참조합니다.

HWND g_hWnd;



struct fPOINT
{
	float x;
	float y;
};
float Miracle = 0;

int Stage;

int MainTile[256][256]; // 타일 속성

POINT MouseMove;
POINT MouseLD;
POINT MouseRD;
POINT MouseState;

POINT g_Camera; // 카메라
POINT Screen;	// 스크린
POINT PlayerPos;

POINT TileSize;		// 타일크기
POINT StageA_Size;	// 맵사이즈
POINT Resolution;	// 해상도

int PlayerSpeed;
float PlayerHp;
float PlayerAttack;
float PlayerDefense;


RECT MonsterTile;

int TileTypeL;
int TileTypeR;
int TileTypeU;
int TileTypeD;

BOOL bRight;
BOOL bLeft;
BOOL bUp;
BOOL bDown;
BOOL bSp;

float g_Delta;

BOOL KeepPotion;
BOOL SetPotion;

