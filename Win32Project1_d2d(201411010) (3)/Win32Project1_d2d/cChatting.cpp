#include "stdafx.h"
#include "cChatting.h"
#include "Network.h"
#include "cGameManager.h"
#include <iostream>
#include <queue>

using namespace std;

extern cGameManager g_pGameManager;


cChatting::cChatting()
{
	m_ChattingArea.left = 100;
	m_ChattingArea.top = 500;
	m_ChattingArea.right = m_ChattingArea.left + 300;
	m_ChattingArea.bottom = m_ChattingArea.top + 500;

	//m_EditBox.left = m_ChattingArea.left + BOX_PADDING;
	//m_EditBox.top = m_ChattingArea.top + BOX_PADDING;
	//m_EditBox.right = m_EditBox.left + EDITBOX_WIDTH;
	//m_EditBox.bottom = m_EditBox.top + EDITBOX_HEIGHT;

	m_EditBox.left = m_ChattingArea.left + BOX_PADDING;
	m_EditBox.top = m_ChattingArea.top + BOX_PADDING;
	m_EditBox.right = m_EditBox.left + EDITBOX_WIDTH;
	m_EditBox.bottom = m_EditBox.top + EDITBOX_HEIGHT;

	//m_nListStartX = m_ChattingArea.left + BOX_PADDING;
	//m_nListStartY = m_EditBox.bottom + BOX_PADDING;  // edit box 아래로 위치시킴.

	ChatBoard = nullptr;
}


cChatting::~cChatting()
{
	m_vecChatList.clear();

	SafeRelease(ChatBoard);
}

void cChatting::OnCommand(WPARAM wParam)
{
	int wmId, wmEvent;
	wmId = LOWORD(wParam);
	wmEvent = HIWORD(wParam);
	// 메뉴 선택을 구문 분석합니다.

	switch (wmId)
	{
	case BTN_CHAT_SEND:
	{
			wchar_t strChat[128];
			GetWindowText(m_hEditWnd, strChat, 128);
			SendChatMsg(strChat);
			SetWindowText(m_hEditWnd, L"");
	}
		break;
	case CHAT_EXIT:
	{
		DestroyWindow(m_hEditWnd);
		DestroyWindow(m_hBtnWnd);
		DestroyWindow(m_hExitWnd);
		g_Delta = 0;
		MouseMove = { 0, 0 };
		MouseLD = { 0, 0 };
		MouseRD = { 0, 0 };
		MouseState = { 0, 0 };
		Stage = 1;
		//break;
	}
	}
}
void cChatting::OnCreate(HWND hWnd, HINSTANCE hInst)
{
	m_hEditWnd = CreateWindow(L"edit",
		NULL,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
		m_ChattingArea.left + BOX_PADDING, 
		m_ChattingArea.top + BOX_PADDING, 
		EDITBOX_WIDTH,
		EDITBOX_HEIGHT,
		hWnd,
		(HMENU)EIDT_CHAT_INPUT,
		hInst,
		NULL);

	m_hBtnWnd = CreateWindow(L"button",
		L"Send",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		m_ChattingArea.left + BOX_PADDING + 510,
		m_ChattingArea.top + BOX_PADDING, 
		SEND_BTN_WIDTH, 
		SEND_BTN_HEIGHT,
		hWnd,
		(HMENU)BTN_CHAT_SEND,
		hInst,
		NULL);

	m_hExitWnd = CreateWindow(L"button",
		L"Return Game",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		m_ChattingArea.left + BOX_PADDING + 510,
		m_ChattingArea.top + BOX_PADDING + 50,
		SEND_BTN_WIDTH,
		SEND_BTN_HEIGHT,
		hWnd,
		(HMENU)CHAT_EXIT,
		hInst,
		NULL);

	SetEnable(true);
}

void cChatting::OnDisable()
{
	ShowWindow(m_hEditWnd, SW_HIDE);
}

void cChatting::OnEnable()
{
	ShowWindow(m_hEditWnd, SW_SHOW);
}

void cChatting::Render(cD2DRenderer& renderer)
{
	for (int i = 0; i < m_vecChatList.size(); ++i)
	{

		if (m_vecChatList.size() > 0)
		{
			UINT32 cTextLength_c = (UINT32)wcslen(m_vecChatList[i].c_str());

			D2D1_RECT_F layoutRect = D2D1::RectF(
				100,
				50 + i * 20, 
				700,
				300 + i * 20
				);

			renderer.GetRenderTarget()->DrawTextW(
				m_vecChatList[i].c_str(),
				cTextLength_c,
				renderer.GetTextFormat(),
				layoutRect,
				renderer.GetBrush());
		}

	}

}

void cChatting::ChatBoardRender(cD2DRenderer& renderer)
{
	if (ChatBoard != nullptr);
	{
		D2D1_SIZE_U size = renderer.GetRenderTargetSize();
		::D2D1_RECT_F dxArea = ::D2D1::RectF(0, 0, Resolution.x, Resolution.y);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 800.0f, 600.0f);
		renderer.GetRenderTarget()->DrawBitmap(ChatBoard, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}
}

void cChatting::LoadImages(cD2DRenderer& renderer, HWND hWnd)
{
	ChatBoard = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Chat/ChatBoard.png");
}

void cChatting::OnChat(char* packet, int nRecv)
{

	packet[nRecv] = '\0';
	wchar_t wBuf[1024];
	MultiByteToWideChar(CP_ACP, 0, packet, -1, wBuf, 1024);
	//채팅 문자를 WM_PAINT 에서 뿌리기 위해 저장
	std::wstring chat = wBuf;
	m_vecChatList.push_back(chat);
	//윈도우 타이틀에 한번 뿌려본다.
	//SetWindowText(g_hWnd, chat.c_str());

}