#include <CoreDefine.h>
#include <MainEntry.h>
#include <System.h>

constexpr int screenStartLeft = 10;
constexpr int screenStartTop = 10;

void Engine::MainEntry::Initialize(GameSettings gameSettings)
{
	const TCHAR* title = gameSettings.title;

	WNDCLASS wndClass{};

	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = gameSettings.hInstance;
	wndClass.hIcon = LoadIcon(gameSettings.hInstance, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = title;

	RegisterClass(&wndClass);

	RECT windowRect
	{
		screenStartLeft, 
		screenStartTop,
		screenStartLeft + gameSettings.width, 
		screenStartTop + gameSettings.height 
	};

	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

	gameSettings.hWnd = CreateWindow
	(
		title,
		title,
		WS_OVERLAPPEDWINDOW,
		windowRect.left,
		windowRect.top,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		(HMENU)NULL,
		gameSettings.hInstance,
		NULL
	);

	ShowWindow(gameSettings.hWnd, SW_SHOWNORMAL);
	UpdateWindow(gameSettings.hWnd);

	_pSystem = System::Create(std::move(gameSettings));
}

void Engine::MainEntry::MainLoop()
{
		MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
				break;
			else
			{
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (!_pSystem->MainLoop())
				break;
		}
	}
}

void Engine::MainEntry::Terminate()
{
	if(_pSystem)
		SafeDelete(_pSystem);

}

LRESULT Engine::MainEntry::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
