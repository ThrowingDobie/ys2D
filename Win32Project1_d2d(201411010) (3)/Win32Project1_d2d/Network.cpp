#include "stdafx.h"
#include "Network.h"
#include "Packet.h"
#include "cGameManager.h"

extern cGameManager* g_pGameManager;
SOCKET g_hSock;

void NetworkStart()
{
	//Winsock Start up
	int ret;
	WSADATA wsa;
	SOCKADDR_IN saddr;

	ret = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (ret != 0)
	{
		ErrorDisplay(L"WSAStartup Error ");
	}

	g_hSock = socket(AF_INET, SOCK_STREAM, 0);
	if (g_hSock == INVALID_SOCKET)
	{
		ErrorDisplay(L"socket() Error ");
	}

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//서버 접속( 접속 성공하면 return )
	ret = connect(g_hSock, (SOCKADDR*)&saddr, sizeof(saddr));
	if (ret != 0)
	{
		ErrorDisplay(L"connect()");
	}

	_beginthread(ReceiveThread, 0, NULL);
}

void NetworkEnd()
{	
	closesocket(g_hSock);
	WSACleanup();
}

void ErrorDisplay(wchar_t* szError)
{
	LPVOID lpBuff;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),//에러코드를 읽어옴
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpBuff,
		0,
		NULL);
	MessageBox(g_hWnd, (LPCTSTR)lpBuff, szError, MB_ICONSTOP);
	LocalFree(lpBuff);
	SendMessage(g_hWnd, WM_DESTROY, NULL, NULL);
	::PostQuitMessage(0);
}

void SendChatMsg(wchar_t* message)
{

	int nSend;
	PACKET::CG_CHAT packet;
	WideCharToMultiByte(CP_ACP,
		0,
		message,
		-1,
		packet.chatData,
		128,
		NULL,
		NULL);
	//sprintf(packet.chatData, "%s", message);
	packet.base.type = PACKET::eType::CG_REQ_CHAT;
	packet.base.size = PACKET::HEADER_SIZE + strlen(packet.chatData);

	nSend = send(g_hSock, (const char*)&packet, packet.base.size, 0);
	if (nSend == SOCKET_ERROR)
	{
		ErrorDisplay(L"sned()");
	}
}

void ReceiveThread(void* params)
{
	char buf[1024];
	while (1)
	{
		int nRecv = recv(g_hSock, buf, sizeof(buf), 0);
		if (nRecv == SOCKET_ERROR)
		{
			ErrorDisplay(L"recv()");
			break;
		}
		else if (nRecv == 0)
		{
			MessageBox(
				NULL,
				L"서버와의 접속이 끊어졌습니다.",
				L"네트워크 에러",
				MB_OK);
			break;
		}
		else
		{
			g_pGameManager->OnChat(buf, nRecv);
		}
	}

	_endthread();
}