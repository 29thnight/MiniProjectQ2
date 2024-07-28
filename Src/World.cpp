#include <Actor.h>
#include <CameraActor.h>
#include <GraphicsManager.h>
#include <CameraComponent.h>
#include <SceneComponent.h>
#include <CoreManager.h>
#include <Object.h>
#include <Level.h>
#include <Layer.h>
#include <World.h>
#include <Mathf.h>
#include <ACollision.h>

bool Engine::World::InitializeWorld(int layerSize)
{
	bool result{};
    result = InitializeLayer(layerSize);
	if(!result)
	{
		return result;
	}

#ifdef _DEBUG
		result = Graphics->AddBrush("Debug", ChooseColor(Palette::White));
		if (!result)
		{
			return result;
		}
#endif // _DEBUG

	return result;
}

bool Engine::World::BeginPlayEnd()
{
	for (auto iter = _vecLevels.begin(); iter != _vecLevels.end(); iter++)
	{
		(*iter)->SettingCamera(_pCameraActor);
	}

	return true;
}

void Engine::World::Destroy()
{
	SafeDelete(_pCameraActor);
	ClearLevel();
	ClearLayer();
}

bool Engine::World::BeginPlay()
{
	for (auto iter = _vecLevels.begin(); iter != _vecLevels.end(); iter++)
	{
		(*iter)->BeginPlay();
	}

	return true;
}

void Engine::World::Tick(_float deltaSeconds)
{
	for (auto iter = _vecLevels.begin(); iter != _vecLevels.end(); iter++)
	{
		(*iter)->Tick(deltaSeconds);
	}
}

void Engine::World::Fixed()
{
	for (auto iter = _vecLevels.begin(); iter != _vecLevels.end(); iter++)
	{
		(*iter)->Fixed();
	}
}

void Engine::World::Render(_RenderTarget pRenderTarget)
{

#ifdef _DEBUG
	DebugDrawGrid(pRenderTarget);
#endif // _DEBUG


	for(auto iter = _vecLayers.begin(); iter != _vecLayers.end(); iter++)
	{
		(*iter)->Render(pRenderTarget);
	}
}

void Engine::World::EndPlay()
{
	for (auto iter = _vecLevels.begin(); iter != _vecLevels.end(); iter++)
	{
		(*iter)->EndPlay();
	}
}

Engine::Level* Engine::World::GetLevel(int levelIndex) const
{
	if (levelIndex < _vecLevels.size())
	{
		return _vecLevels[levelIndex];
	}

	return nullptr;
}

void Engine::World::ContainLevel(Level* pLevel)
{
	_vecLevels.push_back(pLevel);
}

void Engine::World::RemoveLevel(int levelIndex)
{
	for (auto iter = _vecLevels.begin(); iter != _vecLevels.end(); iter++)
	{
		if (*iter == _vecLevels[levelIndex])
		{
			SafeDelete(*iter);
			_vecLevels.erase(iter);
			break;
		}
	}
}

void Engine::World::ClearLevel()
{
	for (auto iter = _vecLevels.begin(); iter != _vecLevels.end(); iter++)
	{
		SafeDelete(*iter);
	}

	_vecLevels.clear();
}

bool Engine::World::InitializeLayer(int layerSize)
{
    _layerSize = layerSize;
	for (int i = 0; i < _layerSize; i++)
	{
		Layer* pLayer = Layer::InitializeLayer(i);
		_vecLayers.push_back(pLayer);
	}

	return true;
}

Engine::Layer* Engine::World::GetLayer(int layerIndex) const
{
	if (layerIndex < _vecLayers.size())
	{
		return _vecLayers[layerIndex];
	}

	return nullptr;
}

void Engine::World::AddLayer(int layerIndex, Layer* pLayer)
{
	_vecLayers.push_back(pLayer);
}

void Engine::World::RemoveLayer(int layerIndex)
{
	for(auto iter = _vecLayers.begin(); iter != _vecLayers.end(); iter++)
	{
		if (*iter == _vecLayers[layerIndex])
		{
			SafeDelete(*iter);
			_vecLayers.erase(iter);
			break;
		}
	}
}

void Engine::World::ClearLayer()
{
	for(auto iter = _vecLayers.begin(); iter != _vecLayers.end(); iter++)
	{
		(*iter)->Destroy();
	}

	_vecLayers.clear();
}

void Engine::World::SettingCamera(CameraActor* pCameraActor)
{
	if(!pCameraActor)
	{
		_pCameraActor = CameraActor::Create();
		_pCameraActor->SetWorld(this);
		_pCameraActor->SetName("MainCamera");
		return;
	}

	_pCameraActor = pCameraActor;
	_pCameraActor->SetWorld(this);
}

void Engine::World::SettingCameraPosition(Mathf::Vector2 position)
{
	_pCameraActor->GetCameraComponent()->SetRelativeLocation(position);
}

void Engine::World::SettingTrackingCameraTarget(Actor* pTargetActor)
{
	_pCameraActor->TrackTarget(pTargetActor);
	_pCameraActor->SettingTracking(true);
}

void Engine::World::SetCameraLerpFactor(float lerpFactor)
{
	_pCameraActor->SetCameraLerpFactor(lerpFactor);
}

void Engine::World::SettingTrackingCamera(bool isTracking)
{
	_pCameraActor->SettingTracking(isTracking);
}

bool Engine::World::IsTrackingCamera() const
{
	return _pCameraActor->IsTracking();
}

void Engine::World::SettingCameraOffset(Mathf::Vector2 offset)
{
	_pCameraActor->GetCameraComponent()->SetCameraOffset(offset);
}

Engine::Actor* Engine::World::FindActor(_pstring name)
{
    return _actorMap.find(name)->second;
}

bool Engine::World::SpawnActor(int layerIndex, _pstring name, Actor* pActor)
{
	pActor->SetName(name);
	pActor->SetRootComponent(pActor->AddComponent<SceneComponent>("RootComponent"));
	pActor->SetLayerIndex(layerIndex);

	_actorMap.insert(std::make_pair(name, pActor));
	_vecLevels[_currentLevelIndex]->AddActor(pActor);
	
	pActor->BeginPlay();

	return true;
}

bool Engine::World::SpawnActor(int layerIndex, _pstring name, Actor* pActor, Mathf::Vector2 location)
{
	pActor->SetName(name);
	pActor->SetRootComponent(pActor->AddComponent<SceneComponent>("RootComponent"));
	pActor->SetLayerIndex(layerIndex);
	pActor->SetWorld(this);
	pActor->GetRootComponent()->SetRelativeLocation(location);

	_actorMap.insert(std::make_pair(name, pActor));
	_vecLevels[_currentLevelIndex]->AddActor(pActor);
	
	pActor->BeginPlay();

	return true;
}

bool Engine::World::RemoveActor(_pstring name)
{
	_actorMap.find(name)->second->OnDestroyMark();

	return true;
}

bool Engine::World::ReviveActor(_pstring name)
{
	Actor* pActor = static_cast<Actor*>(CoreManager::GetInstance()->FindDestroyList(name));
	if (pActor)
	{
		pActor->OnRevive();
		_actorMap.insert(std::make_pair(name, pActor));
		_vecLevels[_currentLevelIndex]->InsertActor(pActor);
		pActor->ReviveInitialize();
		pActor->SetWorld(this);
		CoreManager::GetInstance()->UnRegisterDestroyList(pActor);

		return true;
	}

	return false;
}

void Engine::World::DebugDrawGrid(_RenderTarget pRenderTarget)
{
	Mathf::SizeF size = pRenderTarget->GetSize();

	for (float i = 0; i < size.width; i += 100.f)
	{
		pRenderTarget->DrawLine(Mathf::Point2F{ i, 0.f }, Mathf::Point2F{ i, (float)size.height }, Graphics->GetBrush("Debug"));
	}

	for (float i = 0; i < size.height; i += 100.f)
	{
		pRenderTarget->DrawLine(Mathf::Point2F{ 0.f, i }, Mathf::Point2F{ (float)size.width, i }, Graphics->GetBrush("Debug"));
	}
}
