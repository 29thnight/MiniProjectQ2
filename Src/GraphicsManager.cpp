#include <CoreDefine.h>
#include <CoreManager.h>
#include <GraphicsManager.h>

HRESULT Engine::GraphicsManager::Initialize()
{
	HRESULT hresult{ S_FALSE };
	HWND hWnd = Management->setting.hWnd;
	hresult = InitializeD2D(hWnd);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to Initialize", L"Error", MB_OK);
		return hresult;
	}

	return hresult;
}

HRESULT Engine::GraphicsManager::AddBrush(_pstring brushName, const Color& color)
{
	HRESULT hresult{ S_FALSE };

	SmartPtr<ID2D1SolidColorBrush> pBrush{};
	hresult = _pRenderTarget->CreateSolidColorBrush(color, pBrush.GetAddressOf());
	if (FAILED(hresult))
	{
		MessageBoxW(nullptr, L"Failed to Create Solid Brush", L"Error", MB_OK);
		return hresult;
	}

	_solidBrush[brushName] = pBrush;
	return hresult;
}

ID2D1SolidColorBrush* Engine::GraphicsManager::GetBrush(_pstring brushName)
{
	return _solidBrush[brushName].Get();
}

void Engine::GraphicsManager::Destroy()
{
	SafeRelease(_pWICFactory);
	CoUninitialize();
}

HRESULT Engine::GraphicsManager::InitializeD2D(HWND hWnd, bool isEditor)
{
	HRESULT hresult{ S_FALSE };
	hresult = CoInitialize(nullptr);
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to CoInitialize", L"Error", MB_OK);
		return hresult;
	}

	hresult = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&_pWICFactory));
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to Create WICImagingFactory", L"Error", MB_OK);
		return hresult;
	}
	Management->WICFactory = _pWICFactory;

	hresult = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, _pD2DFactory.GetAddressOf());
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to Create D2D1Factory", L"Error", MB_OK);
		return hresult;
	}

	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties{};
	D2D1_PRESENT_OPTIONS presentOptions{ D2D1_PRESENT_OPTIONS_IMMEDIATELY };

	renderTargetProperties.type = D2D1_RENDER_TARGET_TYPE_HARDWARE;
	renderTargetProperties.pixelFormat.format = DXGI_FORMAT_UNKNOWN;
	renderTargetProperties.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;

	D2D1_SIZE_U screenSize{};
	if(isEditor)
	{
		screenSize = D2D1::SizeU(1920U, 1080U);
	}
	else
	{
		screenSize = D2D1::SizeU(Management->setting.width, Management->setting.height);
	}

	hresult = _pD2DFactory->CreateHwndRenderTarget(renderTargetProperties, 
		D2D1::HwndRenderTargetProperties(hWnd, screenSize, presentOptions), _pRenderTarget.GetAddressOf());
	if (FAILED(hresult))
	{
		MessageBoxW(hWnd, L"Failed to Create HwndRenderTarget", L"Error", MB_OK);
		return hresult;
	}
	Management->renderTarget = _pRenderTarget.Get();

	return hresult;
}
