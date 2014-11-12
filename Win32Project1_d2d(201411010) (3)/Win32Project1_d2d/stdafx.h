// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#pragma comment( lib, "d2d1.lib" )
#pragma comment( lib, "WindowsCodecs.lib" )
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

extern HWND g_hWnd;

extern class cGameManager;

extern float Miracle;


// �ΰ���

extern int Stage;

extern POINT MouseMove;
extern POINT MouseLD;
extern POINT MouseRD;
extern POINT MouseState;

extern int MainTile[256][256];

extern POINT g_Camera;
extern POINT Screen;
extern POINT PlayerPos;

extern POINT TileSize;		// Ÿ��ũ��
extern POINT StageA_Size;	// �ʻ�����
extern POINT Resolution;	// �ػ�

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


