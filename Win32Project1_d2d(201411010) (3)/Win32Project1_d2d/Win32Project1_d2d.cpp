// Win32Project1_d2d.cpp : ���� ���α׷��� ���� �������� �����մϴ�.
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

// ���� ����:
HINSTANCE hInst;								// ���� �ν��Ͻ��Դϴ�.
TCHAR szTitle[MAX_LOADSTRING];					// ���� ǥ���� �ؽ�Ʈ�Դϴ�.
TCHAR szWindowClass[MAX_LOADSTRING];			// �⺻ â Ŭ���� �̸��Դϴ�.




// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
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

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.
	MSG msg;
	HACCEL hAccelTable;

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1_D2D, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���� ���α׷� �ʱ�ȭ�� �����մϴ�.
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}


	//
	g_pGameManager = new cGameManager;
	g_pGameManager->LoadImages(g_d2dRender, g_hWnd);
	g_pGameManager->Load();



	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1_D2D));

	// �⺻ �޽��� �����Դϴ�.
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
//  �Լ�: MyRegisterClass()
//
//  ����: â Ŭ������ ����մϴ�.
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
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   ����: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   ����:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ����:  �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND	- ���� ���α׷� �޴��� ó���մϴ�.
//  WM_PAINT	- �� â�� �׸��ϴ�.
//  WM_DESTROY	- ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
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
		// �޴� ������ ���� �м��մϴ�.
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

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
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
