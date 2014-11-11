#pragma once
#include <Windows.h>
#include <vector>
#include "cD2DRenderer.h"
#define BTN_CHAT_SEND 1
#define EIDT_CHAT_INPUT 2
#define CHAT_EXIT 3
#define BOX_PADDING 5
#define EDITBOX_WIDTH 500
#define EDITBOX_HEIGHT 25
#define SEND_BTN_WIDTH 95
#define SEND_BTN_HEIGHT 25

class cChatting
{
public:
	cChatting();
	~cChatting();
	void Update(float delta){}
	void Render(cD2DRenderer& renderer);
	void OnCommand(WPARAM wParam);
	void SetEnable(bool enable){
		m_bEnable = enable;
		if (m_bEnable)
			OnEnable();
		else
			OnDisable();
	}
	void OnCreate(HWND hWnd, HINSTANCE hInst);
	void OnChat(char* packet, int nRecv);

	void ChatBoardRender(cD2DRenderer&renderer);
	void LoadImages(cD2DRenderer& renderer, HWND hWnd);

private:
	void OnDisable();
	void OnEnable();
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	bool m_bEnable;
	HWND m_hEditWnd;
	HWND m_hBtnWnd;
	HWND m_hExitWnd;
	std::vector<std::wstring> m_vecChatList;
	//queue<string> m_queChatList;
	RECT m_ChattingArea;
	RECT m_EditBox;
	RECT m_SendBtn;
	int m_nListStartX;
	int m_nListStartY;

	ID2D1Bitmap* ChatBoard;

};

