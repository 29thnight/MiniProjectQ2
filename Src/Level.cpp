#include <Level.h>
#include <Actor.h>
#include <Object.h>
#include <World.h>
#include <CoreManager.h>

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


void Engine::Level::Destroy()
{
	for (auto iter = _actors.begin(); iter != _actors.end(); iter++)
	{
		SafeDelete(*iter);
	}

	_actors.clear();
}
