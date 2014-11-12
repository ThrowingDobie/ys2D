// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "WindowsCodecs.lib" )
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

extern HWND g_hWnd;

extern class cGameManager;

extern float Miracle;


// 인게임

extern int Stage;

extern POINT MouseMove;
extern POINT MouseLD;
extern POINT MouseRD;
extern POINT MouseState;

extern int MainTile[256][256];

extern POINT g_Camera;
extern POINT Screen;
extern POINT PlayerPos;

extern POINT TileSize;		// 타일크기
extern POINT StageA_Size;	// 맵사이즈
extern POINT Resolution;	// 해상도

extern int PlayerSpeed;
extern float PlayerHp;
extern float PlayerAttack;
extern float PlayerDefense;

extern RECT MonsterTile;

extern int TileTypeL;
extern int TileTypeR;
extern int TileTypeU;
extern int TileTypeD;

extern BOOL bRight;
extern BOOL bLeft;
extern BOOL bUp;
extern BOOL bDown;
extern BOOL bSp;
extern BOOL bEnt;


extern float g_Delta;

extern BOOL KeepPotion;
extern BOOL SetPotion;



// D2D1
#include <cassert>
#include <commdlg.h>
#include <wincodec.h>
#include <d2d1.h>
#include <d2d1helper.h>
template <typename T>
inline void SafeRelease(T *&p)
{
	if (NULL != p)
	{
		p->Release();
		p = NULL;
	}
}


