#include <Level.h>
#include <Actor.h>
#include <Object.h>
#include <World.h>
#include <CoreManager.h>
#include <SceneComponent.h>
#include <Mathf.h>

void Engine::Level::Tick(_float deltaSeconds)
{
	if(_actors.empty())
		return;

	for(auto& actor : _actors)
	{
		if(actor->IsDestroyMarked())
			continue;

		actor->Tick(deltaSeconds);
	}
}

void Engine::Level::Fixed()
{
	if(_actors.empty())
	return;

	for(auto& actor : _actors)
	{

		if(actor->IsDestroyMarked())
			continue;

		actor->Fixed();
	}
}

void Engine::Level::EndPlay()
{
	if (_actors.empty())
		return;

	for (auto it = _actors.begin(); it != _actors.end();)
	{
		if (nullptr == *it)
		{
			++it;
			continue;
		}

		if (!(*it)->IsDestroyMarked())
		{
			++it;
			continue;
		}

		(*it)->EndPlay();
		Management->AddDestroyList(*it);
		Management->EraseActorMap(*it);
		it = _actors.erase(it); // 요소를 삭제하고 반복자를 다음 요소로 이동
	}
}

bool Engine::Level::InsertActor(Actor* pActor)
{
	_actors.push_back(pActor);

    return true;
}

bool Engine::Level::AddActor(Actor* pActor)
{
    _actors.push_back(pActor);
	pActor->BeginPlay();

    return true;
}

Engine::Actor* Engine::Level::GetActor(_pstring name)
{
    for (auto iter = _actors.begin(); iter != _actors.end(); iter++)
	{
		if (!strcmp((*iter)->GetName(), name))
			return *iter;
	}

	return nullptr;
}

bool Engine::Level::SpawnActor(int layerIndex, _pstring name, Actor* pActor)
{
	pActor->SetName(name);
	pActor->SetRootComponent(pActor->AddComponent<SceneComponent>("RootComponent"));
	pActor->SetLayerIndex(layerIndex);

	_pWorld->GetActorMap().insert(std::make_pair(name, pActor));
	AddActor(pActor);
}

bool Engine::Level::SpawnActor(int layerIndex, _pstring name, Actor* pActor, Mathf::Vector2 location)
{
	pActor->SetName(name);
	pActor->SetRootComponent(pActor->AddComponent<SceneComponent>("RootComponent"));
	pActor->SetLayerIndex(layerIndex);
	pActor->SetWorld(_pWorld);
	pActor->GetRootComponent()->SetRelativeLocation(location);

	_pWorld->GetActorMap().insert(std::make_pair(name, pActor));
	AddActor(pActor);
}

bool Engine::Level::RemoveActor(_pstring name)
{
	_pWorld->GetActorMap().find(name)->second->OnDestroyMark();

	return true;
}

bool Engine::Level::TerminateActor(_pstring name)
{
	Actor* pActor = _pWorld->GetActorMap().find(name)->second;
	pActor->OnCompleteDestroyMark();

	return true;
}

bool Engine::Level::ReviveActor(_pstring name)
{
	Actor* pActor = static_cast<Actor*>(Management->FindDestroyList(name));
	if (pActor)
	{
		pActor->OnRevive();
		_pWorld->GetActorMap().insert(std::make_pair(name, pActor));
		InsertActor(pActor);
		pActor->ReviveInitialize();
		pActor->SetWorld(_pWorld);
		Management->UnRegisterDestroyList(pActor);

		return true;
	}

	return false;
}


void Engine::Level::Destroy()
{
	for (auto iter = _actors.begin(); iter != _actors.end(); iter++)
	{
		SafeDelete(*iter);
	}

	_actors.clear();
}
