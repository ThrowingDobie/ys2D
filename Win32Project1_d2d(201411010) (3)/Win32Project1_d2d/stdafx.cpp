// stdafx.cpp : ǥ�� ���� ���ϸ� ��� �ִ� �ҽ� �����Դϴ�.
// Win32Project1_d2d.pch�� �̸� �����ϵ� ����� �˴ϴ�.
// stdafx.obj���� �̸� �����ϵ� ���� ������ ���Ե˴ϴ�.

#include "stdafx.h"
#include "cGameManager.h"


// TODO: �ʿ��� �߰� �����
// �� ������ �ƴ� STDAFX.H���� �����մϴ�.

HWND g_hWnd;



struct fPOINT
{
	float x;
	float y;
};
float Miracle = 0;

int Stage;

int MainTile[256][256]; // Ÿ�� �Ӽ�

POINT MouseMove;
POINT MouseLD;
POINT MouseRD;
POINT MouseState;

POINT g_Camera; // ī�޶�
POINT Screen;	// ��ũ��
POINT PlayerPos;

POINT TileSize;		// Ÿ��ũ��
POINT StageA_Size;	// �ʻ�����
POINT Resolution;	// �ػ�

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

