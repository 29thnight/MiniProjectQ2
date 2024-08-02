#include <GraphicsManager.h>
#include <CoreManager.h>
#include <TimeManager.h>
#include <InputManager.h>
#include <World.h>
#include <Object.h>
#include <CoreBase.h>
#include <Layer.h>
#include <CollisionManager.h>

Engine::CoreManager::CoreManager()
{
}

void Engine::CoreManager::BeginPlay()
{
	_pCollisionManager = CollisionManager::Create();
}

void Engine::CoreManager::Tick()
{
	Time->UpdateTick();
	InputMgr->InputUpdate();
	setting.pWorld->Tick(Time->DeltaSeconds);
	_pCollisionManager->SimulateCollision();
}

void Engine::CoreManager::Fixed(int count)
{
	if(!count)
	{
		MessageBox(nullptr, L"Fixed count is zero", L"Error", MB_OK);
		return Terminate();
	}
		
	auto fixedTick = std::chrono::nanoseconds(static_cast<int64_t>(1e9 / count));

	if(_elapsedTick >= fixedTick)
	{
		setting.pWorld->Fixed();
		_elapsedTick -= fixedTick;
	}
}

void Engine::CoreManager::Render()
{
	_renderTarget->BeginDraw();

	_renderTarget->Clear();

	setting.pWorld->Render(_renderTarget);

	_renderTarget->EndDraw();
}

void Engine::CoreManager::EndPlay()
{
	setting.pWorld->EndPlay();
}

void Engine::CoreManager::DestroyPoint()
{
	for (auto& pObject : _toBeDestroyed)
	{
		if(pObject->IsCompleteDestroyMarked())
			SafeDelete(pObject);
	}
}

void Engine::CoreManager::Initialize(GameSettings&& gameSettings)
{
	_gameSettings = gameSettings;
}

void Engine::CoreManager::AddDestroyList(Object* pObject)
{
	if (!pObject) return;  // 유효하지 않은 포인터 검증

	_toBeDestroyed.push_back(pObject);
}

void Engine::CoreManager::EraseActorMap(Object* pObject)
{
	setting.pWorld->GetActorMap().erase(pObject->GetName());
}

Engine::Object* Engine::CoreManager::FindDestroyList(_pstring name)
{
	for (auto& pObject : _toBeDestroyed)
	{
		if (pObject->GetName() == name)
		{
			return pObject;
		}
	}

	return nullptr;
}

void Engine::CoreManager::UnRegisterDestroyList(Object* pObject)
{
	for (auto iter = _toBeDestroyed.begin(); iter != _toBeDestroyed.end(); iter++)
	{
		if (*iter == pObject)
		{
			_toBeDestroyed.erase(iter);
			break;
		}
	}
}

Engine::Layer* Engine::CoreManager::GetLayer(int layerIndex)
{
	return setting.pWorld->GetLayer(layerIndex);
}

void Engine::CoreManager::AddRenderQueue(int layerIndex, RenderComponent* pRenderComponent)
{
	Layer* pLayer = setting.pWorld->GetLayer(layerIndex);
	if (!pLayer) return;

	pLayer->AddRenderQueue(pRenderComponent);
}

void Engine::CoreManager::RemoveRenderQueue(int layerIndex, RenderComponent* pRenderComponent)
{
	Layer* pLayer = setting.pWorld->GetLayer(layerIndex);
	if (!pLayer) return;

	pLayer->RemoveRenderQueue(pRenderComponent);
}

void Engine::CoreManager::AddCollisionQueue(int layerIndex, CollisionComponent* pCollsionComponent)
{
	_pCollisionManager->AddCollisionQueue(layerIndex, pCollsionComponent);
}

void Engine::CoreManager::RemoveCollisionQueue(int layerIndex, CollisionComponent* pCollsionComponent)
{
	_pCollisionManager->RemoveCollisionQueue(layerIndex, pCollsionComponent);
}

void Engine::CoreManager::Destroy()
{
	for (auto& pObject : _toBeDestroyed)
	{
		SafeDelete(pObject);
	}
	_toBeDestroyed.clear();

	setting.pWorld->Terminate();
	SafeDelete(_pCollisionManager);

	_isDestroy = true;
}
