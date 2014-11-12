#pragma once

#include <vector>

#include "cD2DRenderer.h"

#include "cChatting.h"

class cGameManager
{
protected:



public:
	cGameManager();
	~cGameManager();

	void KeyDown(DWORD dwKey);
	void KeyUp(DWORD dwKey);
	void Save();
	void Load();

	void Render(cD2DRenderer& renderer);
	void Update(float timeDelta);
	void LoadImages(cD2DRenderer& renderer, HWND hWnd);
	void GetCrushMonster(int* arr);
	void GetCrushNPC(int* arr);

	// Ã¤ÆÃ
	void OnCreate(HWND hWnd, HINSTANCE hInst);
	void ChatRender(cD2DRenderer& renderer);
	void OnCommand(WPARAM wParam);
	void OnChat(char* packet, int nRecv);

private:
	cChatting m_Chatting;
};

