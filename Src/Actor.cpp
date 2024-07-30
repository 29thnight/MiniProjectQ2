#include <Actor.h>
#include <SceneComponent.h>
#include <TextureManager.h>
#include <ActorComponent.h>
#include <ObjectPtr.h>

void Engine::Actor::BeginPlay()
{
	Object::CreateObjectDirectory();

	string convertName = (string)"Assets/" + this->_name;

	_vecTextures.push_back(TextureMgr->FindTexture(convertName));
}

void Engine::Actor::Tick(_float deltaSeconds)
{
	for (auto& component : _vecComponents)
	{
		component->TickComponent(deltaSeconds);
	}
}

void Engine::Actor::Fixed()
{
}

void Engine::Actor::EndPlay()
{
}

bool Engine::Actor::SetRootComponent(SceneComponent* pRootComponent)
{
	_pRootComponent = pRootComponent;

	return true;
}

void Engine::Actor::AttachToActor(Actor* pParent)
{
	_pParent = pParent;
	_pRootComponent->AttachToComponent(_pParent->GetRootComponent());
}

void Engine::Actor::DetachFromActor()
{
	_pRootComponent->AttachToComponent(nullptr);
	_pParent = nullptr;
}

void Engine::Actor::PushBackComponent(ActorComponent* pComponent)
{
	_vecComponents.push_back(MakeObjectPtr<ActorComponent>(pComponent));
}

void Engine::Actor::Destroy()
{
	_vecComponents.clear();
	_vecTextures.clear();
	_pRootComponent = nullptr;
	_pParent = nullptr;
}
