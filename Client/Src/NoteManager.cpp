#include <NoteManager.h>
#include <SceneComponent.h>
#include <SoundManager.h>


using namespace Engine;

void Client::NoteManager::BeginPlay()
{
	Base::BeginPlay();
	Sound->PlaySound("Sound/test", 0, 0);
}

void Client::NoteManager::Tick(_duration deltaSeconds)
{
	Base::Tick(deltaSeconds);
}

void Client::NoteManager::Fixed()
{
	
}

void Client::NoteManager::EndPlay()
{
	
}

void Client::NoteManager::NotifyActorBlock(Engine::CollisionData data)
{
}

void Client::NoteManager::NotifyActorBeginOverlap(Engine::CollisionData data)
{
}

void Client::NoteManager::NotifyActorEndOverlap(Engine::CollisionData data)
{
}

void Client::NoteManager::SetupInputComponent(Engine::InputComponent* inputComponent)
{
}

void Client::NoteManager::SerializeIn(nlohmann::ordered_json& object)
{
}

void Client::NoteManager::SerializeOut(nlohmann::ordered_json& object)
{
}
