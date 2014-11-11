#include "stdafx.h"
#include "cOpening.h"


cOpening::cOpening()
{
	Opening = nullptr;
	Opening_Box = nullptr;
	GameStart_Line = nullptr;
	Exit_Line = nullptr;
}


cOpening::~cOpening()
{
	SafeRelease(Opening);
	SafeRelease(Opening_Box);
	SafeRelease(GameStart_Line);
	SafeRelease(Exit_Line);
}

void cOpening::Update()
{
	//RECT Box = { 400 - (310 / 4),
	//	300 - (130 / 4) + 50,
	//	400 + (310 / 4),
	//	300 + (130 / 4) + 50 };

	if ((MouseMove.x >= 330) &&
		(MouseMove.x <= 470) && 
		(MouseMove.y >= 275+50) && 
		(MouseMove.y <= 300+50)) 
		MouseOn = 1;
	else if ((MouseMove.x >= 330) &&
		(MouseMove.x <= 470) &&
		(MouseMove.y >= 301+50) &&
		(MouseMove.y <= 325+50))
		MouseOn = 2;
	else MouseOn = 0;

	if ((MouseLD.x >= 330) &&
		(MouseLD.x <= 470) &&
		(MouseLD.y >= 275 + 50) &&
		(MouseLD.y <= 300 + 50))
	{
		Stage = 1;
		MouseMove = { 0, 0 };
		MouseLD = { 0, 0 };
		MouseRD = { 0, 0 };
		MouseState = { 0, 0 };
	}

	else if ((MouseLD.x >= 330) &&
		(MouseLD.x <= 470) &&
		(MouseLD.y >= 301 + 50) &&
		(MouseLD.y <= 325 + 50))
		Stage = 99; // 종료화면
}

void cOpening::Render(cD2DRenderer& renderer)
{
	if (Opening != nullptr);
	{
		D2D1_SIZE_U size = renderer.GetRenderTargetSize();
		::D2D1_RECT_F dxArea = ::D2D1::RectF(0, 0, Resolution.x, Resolution.y);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 1600, 1200);
		renderer.GetRenderTarget()->DrawBitmap(Opening, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	if (Opening_Box != nullptr);
	{
		D2D1_SIZE_U size = renderer.GetRenderTargetSize();
		::D2D1_RECT_F dxArea = ::D2D1::RectF(400-(310/4), 300-(130/4)+50, 400+(310/4), 300+(130/4)+50);
		::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 310, 130);
		renderer.GetRenderTarget()->DrawBitmap(Opening_Box, dxArea, 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			srcArea);
	}

	if (MouseOn == 1)
	{
		if (GameStart_Line != nullptr)
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				400 - (310 / 4),
				300 - (130 / 4) + 57,
				400 + (310 / 4),
				300 + (130 / 8) + 33);
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 310, 130);
			renderer.GetRenderTarget()->DrawBitmap(GameStart_Line, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}

	}
	else if (MouseOn == 2)
	{
		if (Exit_Line != nullptr)
		{
			D2D1_SIZE_U size = renderer.GetRenderTargetSize();
			::D2D1_RECT_F dxArea = ::D2D1::RectF(
				400 - (310 / 4),
				300 + (130 / 8) + 33,
				400 + (310 / 4),
				300 + (130 / 4) + 40);
			::D2D1_RECT_F srcArea = ::D2D1::RectF(0, 0, 310, 130);
			renderer.GetRenderTarget()->DrawBitmap(Exit_Line, dxArea, 1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				srcArea);
		}
	}

}

void cOpening::LoadImages(cD2DRenderer& renderer, HWND hWnd)
{
	Opening = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Opening/Opening.png");
	Opening_Box = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Opening/Opening_Box.png");
	GameStart_Line = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Opening/GameStart_Line.png");
	Exit_Line = renderer.CreateD2DBitmapFromFile(hWnd, L"Images/Opening/Exit_Line.png");
}
