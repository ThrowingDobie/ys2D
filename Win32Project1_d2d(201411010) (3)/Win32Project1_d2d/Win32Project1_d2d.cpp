// Win32Project1_d2d.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Win32Project1_d2d.h"
#include "cD2DRenderer.h"


#include "cGameManager.h"

#include "Network.h"


#include <WinSock2.h>
#include <process.h>
#include <vector>



#pragma comment(lib, "ws2_32.lib")


#define MAX_LOADSTRING 100
#define TIMER_ID 1
#define TIMER_INTERVAL 50

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
TCHAR szTitle[MAX_LOADSTRING];					// 제목 표시줄 텍스트입니다.
TCHAR szWindowClass[MAX_LOADSTRING];			// 기본 창 클래스 이름입니다.




// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

cD2DRenderer g_d2dRender;

cGameManager* g_pGameManager = nullptr;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	NetworkStart();

	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	HACCEL hAccelTable;

	// 전역 문자열을 초기화합니다.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1_D2D, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}


	//
	g_pGameManager = new cGameManager;
	g_pGameManager->LoadImages(g_d2dRender, g_hWnd);
	g_pGameManager->Load();



	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1_D2D));

	// 기본 메시지 루프입니다.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	//
	delete g_pGameManager;

	NetworkEnd();

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT1_D2D));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WIN32PROJECT1_D2D);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	hWnd = CreateWindow(szWindowClass, L"YS-Eternal", WS_OVERLAPPEDWINDOW,
		100, 100, (800 + 16), (600 + 58), NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	g_d2dRender.InitializeD2D();
	g_d2dRender.Setup(hWnd);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	g_hWnd = hWnd;
	return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	RECT rc;


	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, TIMER_ID, TIMER_INTERVAL, NULL);

		
		/*if (Stage == 93) g_pGameManager->OnCreate(hWnd, hInst);*/

		break;
	case WM_TIMER:
		if (g_pGameManager != nullptr)
		{
			g_pGameManager->Update(30.0f / 1000.0f);
			if (Stage == 97 && g_Delta == 0)
			{
				g_Delta = 1;
				g_pGameManager->OnCreate(hWnd, hInst);
			}

			
			::InvalidateRect(hWnd, NULL, FALSE);
		}
		break;

	case WM_KEYDOWN:
		if (g_pGameManager != nullptr)
			g_pGameManager->KeyDown(wParam);
		break;

	case WM_KEYUP:
		if (g_pGameManager != nullptr)
			g_pGameManager->KeyUp(wParam);
		break;

	case WM_MOUSEMOVE:
		MouseMove.x = LOWORD(lParam);
		MouseMove.y = HIWORD(lParam);
		break;

	case WM_LBUTTONDOWN:
		MouseLD.x = LOWORD(lParam);
		MouseLD.y = HIWORD(lParam);
		MouseState.x = 1;
		break;

	case WM_RBUTTONDOWN:
		MouseRD.x = LOWORD(lParam);
		MouseRD.y = HIWORD(lParam);
		MouseState.y = 1;
		break;

	case WM_LBUTTONUP:
		MouseState.x = 0;
		break;

	case WM_RBUTTONUP:
		MouseState.y = 0;
		break;

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		if (g_pGameManager != nullptr)
			g_pGameManager->OnCommand(wParam);

		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_SIZE:
		if (g_d2dRender.m_ipRT != nullptr)
		{
			GetClientRect(hWnd, &rc);
			D2D1_SIZE_U size;
			size.width = rc.right - rc.left;
			size.height = rc.bottom - rc.top;

			g_d2dRender.m_ipRT->Resize(size);
		}
		break;

	case WM_PAINT:


	{
		g_d2dRender.BeginRender(hWnd);
		HRESULT hr = E_FAIL;
		g_d2dRender.GetRenderTarget()->BeginDraw();
		g_d2dRender.GetRenderTarget()->SetTransform(::D2D1::Matrix3x2F::Identity());
		g_d2dRender.GetRenderTarget()->Clear(::D2D1::ColorF(::D2D1::ColorF::White));

		if (g_pGameManager != nullptr)
			g_pGameManager->Render(g_d2dRender);

		hr = g_d2dRender.GetRenderTarget()->EndDraw();
		assert(hr == S_OK);

		g_d2dRender.EndRender();
	}

		//hdc = BeginPaint(hWnd, &ps);

		//g_pGameManager->ChatRender(hdc);

		//EndPaint(hWnd, &ps);

		break;
	case WM_DESTROY:
		KillTimer(hWnd, TIMER_ID);

		g_pGameManager->Save();

		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
