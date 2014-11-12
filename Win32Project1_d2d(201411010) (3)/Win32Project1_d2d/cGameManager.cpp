#include "stdafx.h"
#include "cGameManager.h"
//
#include"cD2DRenderer.h"

#include "cBoard.h"
#include "cPlayer.h"
#include "cMapObject.h"
#include "cInterFace.h"
#include "cOpening.h"
#include "cMonster.h"
#include "cEquip.h"
#include "cInven.h"
#include "cNPC.h"
//
cBoard Board;
cPlayer Player;
cMapObject MapObject;
cInterFace InterFace;
cOpening Opening;
cMonster Monster;
cMonster MonsterA;
cEquip Equip;
cInven Inven;
cNPC NPC;

cGameManager::cGameManager()
{
	Stage = 0;
	TileSize = { 20, 20 };
	StageA_Size = { 2048, 1784 };
	Resolution = { 800, 600 };

	Monster.MonsterPos = { 1250, 1200 };
	MonsterA.MonsterPos = { 200, 200 };


}


cGameManager::~cGameManager()
{
}

void cGameManager::KeyDown(DWORD dwKey)
{
	Player.KeyDown(dwKey);
}

void cGameManager::KeyUp(DWORD dwKey)
{
	Player.KeyUp(dwKey);
}

void cGameManager::Save()
{
	Board.TileSave();
}

void cGameManager::Load()
{
	Board.TileLoad();
}

void cGameManager::GetCrushMonster(int* arr)
{
	arr[0] = Monster.GetCrushOn_t(0);
	arr[1] = MonsterA.GetCrushOn_t(1);
}

void cGameManager::GetCrushNPC(int* arr)
{
	arr[0] = NPC.NPC_Host_Event(0);
}

void cGameManager::Update(float timeDelta)
{
	if (Stage == 0)
	{
		Opening.Update();
	}

	if (Stage == 1)
	{
		Player.Update();
		Player.PlayerMove();
		MapObject.Update();
		InterFace.Update();
		Monster.Update();
		Monster.MonsterMove();
		MonsterA.Update();
		MonsterA.MonsterMove();
		NPC.Update();
	}

	if (Stage == 2)
	{

	}



	if (Stage == 94)
	{
		Equip.Update();
		Equip.RenderUpdate();
	}

	if (Stage == 95)
	{
		Inven.Update();
		Inven.RenderUpdate();
	}

	if (Stage == 97)
	{
		m_Chatting.Update(timeDelta);
	}

	if (Stage == 99)
	{
		DestroyWindow;
		PostQuitMessage(0);
	}

	

}

void cGameManager::Render(cD2DRenderer& renderer)
{
	MapObject.DataRender(renderer);

	if (Stage == 0)
	{
		Opening.Render(renderer);
	}

	if (Stage == 1)
	{
		Board.Render(renderer);
		Player.Render(renderer);

		NPC.Render(renderer);

		MapObject.FrontBuildingRender(renderer);
		MapObject.Render(renderer);
		if (Miracle == 1) Player.Render(renderer);

		//
		Monster.Render(renderer);
		MonsterA.Render(renderer);
		
		Player.EffectRender(renderer);

		InterFace.Render(renderer);



		Monster.MonsterHpRender(renderer);
		Monster.EffectRender(renderer);
		MonsterA.MonsterHpRender(renderer);
		MonsterA.EffectRender(renderer);
		//

		NPC.SpeechRender(renderer);

		Player.PlayerHpRender(renderer);
		InterFace.MenuBarRender(renderer);
	}



	if (Stage == 94)
	{
		Equip.Render(renderer);
	}

	if (Stage == 95)
	{
		Inven.Render(renderer);
	}

	if (Stage == 97)
	{
		m_Chatting.ChatBoardRender(renderer);
		m_Chatting.Render(renderer);
	}


}



void cGameManager::LoadImages(cD2DRenderer& renderer, HWND hWnd)
{
	//if (Stage == 0)
	{
		Opening.LoadImages(renderer, hWnd);
	}

	//if (Stage == 1)
	{
		Board.LoadImages(renderer, hWnd);
		Player.LoadImages(renderer, hWnd);
		MapObject.LoadImages(renderer, hWnd);
		InterFace.LoadImages(renderer, hWnd);
		Monster.LoadImages(renderer, hWnd);
		MonsterA.LoadImages(renderer, hWnd);
	}

	Equip.LoadImages(renderer, hWnd);
	Inven.LoadImages(renderer, hWnd);
	m_Chatting.LoadImages(renderer, hWnd);

	NPC.LoadImages(renderer, hWnd);


}


void cGameManager::OnCreate(HWND hWnd, HINSTANCE hInst)
{
	m_Chatting.OnCreate(hWnd, hInst);
}
void cGameManager::ChatRender(cD2DRenderer& renderer)
{
	m_Chatting.Render(renderer);
}
void cGameManager::OnCommand(WPARAM wParam)
{
	m_Chatting.OnCommand(wParam);
}
void cGameManager::OnChat(char* packet, int nRecv)
{
	m_Chatting.OnChat(packet, nRecv);
}


