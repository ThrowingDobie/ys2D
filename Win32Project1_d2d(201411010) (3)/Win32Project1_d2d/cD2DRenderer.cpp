#include "stdafx.h"
#include "cD2DRenderer.h"

cD2DRenderer::cD2DRenderer()
{

	m_ipD2DFactory = nullptr;
	m_ipRT = nullptr;
	m_ipWICFactory = nullptr;
	m_ipConvertedSrcBmp = nullptr;
}


cD2DRenderer::~cD2DRenderer()
{

	SafeRelease(m_ipWICFactory);
	SafeRelease(m_ipRT);
	SafeRelease(m_ipD2DFactory);

	SafeRelease(m_pBlackBrush);
	SafeRelease(m_pDWriteFactory);
	SafeRelease(m_pTextFormat);

}

void cD2DRenderer::InitializeD2D(void)
{

	HRESULT hr = E_FAIL;

	//-----------------------------------------------------------------------
	//	D2D Factory 를 생성한다.
	//-----------------------------------------------------------------------
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&m_ipD2DFactory);
	assert(hr == S_OK);

	// Create a DirectWrite factory.
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
		);
	assert(hr == S_OK);


	m_pDWriteFactory->CreateTextFormat(
		L"굴림",                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		15.0f,
		L"en-us",
		&m_pTextFormat
		);

	CoInitialize(0);

	//-----------------------------------------------------------------------
	//	Windows Imaging Component Factory 를 생성한다.
	//-----------------------------------------------------------------------
	hr = ::CoCreateInstance(CLSID_WICImagingFactory,
		NULL, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_ipWICFactory));
	assert(hr == S_OK);

}

void cD2DRenderer::InitializeRT(HWND hWnd)
{

	assert(m_ipRT == nullptr);
	assert(hWnd != 0);

	HRESULT hr = E_FAIL;
	RECT rc;
	//rc = { 0, 0, 800, 600 };
	::GetClientRect(hWnd, &rc);


	D2D1_RENDER_TARGET_PROPERTIES dxRTProperties = ::D2D1::RenderTargetProperties();
	m_dxSize = ::D2D1::SizeU(rc.right - rc.left,
		rc.bottom - rc.top);

	hr = m_ipD2DFactory->CreateHwndRenderTarget(dxRTProperties,
		::D2D1::HwndRenderTargetProperties(hWnd, m_dxSize),
		&m_ipRT);
	assert(hr == S_OK);

	// Brush
	hr = m_ipRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&m_pBlackBrush
		);

}


ID2D1Bitmap* cD2DRenderer::CreateD2DBitmapFromFile(HWND hWnd, TCHAR* pImageFullPath)
{
	assert(pImageFullPath != nullptr);
	assert(m_ipWICFactory != nullptr);
	assert(m_ipRT != nullptr);

	HRESULT hr = E_FAIL;

	//----------------------------------------------------------------
	//	디코더를 생성한다.
	//----------------------------------------------------------------
	IWICBitmapDecoder* ipDecoderPtr = nullptr;
	hr = m_ipWICFactory->CreateDecoderFromFilename(pImageFullPath, nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&ipDecoderPtr);
	assert(hr == S_OK);

	//----------------------------------------------------------------
	//	디코더에서 프레임을 얻는다.
	//----------------------------------------------------------------
	IWICBitmapFrameDecode* ipFramePtr = nullptr;
	hr = ipDecoderPtr->GetFrame(0, &ipFramePtr);
	assert(hr == S_OK);

	//----------------------------------------------------------------
	//	프레임을 기반으로 해서 포맷 컨버터를 만든다.
	//----------------------------------------------------------------
	SafeRelease(m_ipConvertedSrcBmp);
	hr = m_ipWICFactory->CreateFormatConverter(&m_ipConvertedSrcBmp);
	assert(hr == S_OK);


	hr = m_ipConvertedSrcBmp->Initialize(ipFramePtr,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom);
	assert(hr == S_OK);

	//----------------------------------------------------------------
	//	컨버트된 데이터를 기반으로 해서 실제 비트맵을 만든다.
	//----------------------------------------------------------------
	ID2D1Bitmap* ipD2DBitmap = nullptr;

	hr = m_ipRT->CreateBitmapFromWicBitmap(m_ipConvertedSrcBmp,
		nullptr,
		&ipD2DBitmap);
	assert(hr == S_OK);


	SafeRelease(ipDecoderPtr);
	SafeRelease(ipFramePtr);

	return ipD2DBitmap;

}

void cD2DRenderer::BeginRender(HWND hWnd)
{
	m_hWnd = hWnd;
	hdc = BeginPaint(hWnd, &ps);


}

void cD2DRenderer::Setup(HWND hWnd)
{
	if (m_ipRT == nullptr)
	{
		InitializeRT(hWnd);

		return;

	}
}

void cD2DRenderer::EndRender()
{

	EndPaint(m_hWnd, &ps);

}