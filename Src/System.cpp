#include <CoreManager.h>
#include <TimeManager.h>
#include <GraphicsManager.h>
#include <TextureManager.h>
#include <FontManager.h>
#include <InputManager.h>
#include <SoundManager.h>
#include <World.h>
#include <System.h>

bool Engine::System::MainLoop()
{
	if(!Management->IsFinalDestroy())
	{
		Management->Tick();
		Management->Fixed(50);
		Management->Render();
		Management->EndPlay();
		Management->DestroyPoint();
		return true;
	}

	return false;
}

bool Engine::System::Initialize(GameSettings&& gameSettings)
{
	if(!gameSettings.pWorld)
    {
		MessageBoxEx(nullptr, L"World is nullptr", L"Error", MB_OK, MB_ICONERROR);
		return false;
    }

	Management->Initialize(std::move(gameSettings));
	Management->BeginPlay();
	Time->Initialize();
	FontMgr->Initialize();
	FontMgr->LoadFonts();
	Graphics->Initialize();
	InputMgr->Initialize();
	TextureMgr->LoadTexture(L"Assets");
	Sound->Initialize(Management->setting.maxSoundGroup);
	Sound->LoadSound("Assets/Sound");
	int layerSize = Management->setting.layerSize;
	Management->setting.pWorld->InitializeWorld(layerSize);
	Management->setting.pWorld->BeginPlay();

#ifdef _DEBUG
	Graphics->AddBrush("Red",D2D1::ColorF(D2D1::ColorF::Red));
#endif // DEBUG

	return true;
}

void Engine::System::Destroy()
{
	ManagementTerminate();
	TimeTerminate();
	FontTerminate();
	TextureTerminate();
	InputTerminate();
	GraphicsTerminate();
}

Engine::System* Engine::System::Create(GameSettings&& gameSettings)
{
	System* pSystem = new System();
	if (pSystem->Initialize(std::move(gameSettings)))
		return pSystem;

	SafeDelete(pSystem);
	return nullptr;
}
