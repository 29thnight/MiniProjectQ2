#include "TestActor.h"
#include <AnimationComponent.h>

void Client::TestActor::BeginPlay()
{
	_pAnimationComponent = AddComponent<Engine::AnimationComponent>("AnimationComponent");
	//_pAnimationComponent->AllAddClipThisActor();
	_pAnimationComponent->SetPlayClip("Idle");
}

void Client::TestActor::Tick(_duration deltaSeconds)
{
	Super::Tick(deltaSeconds);
}

void Client::TestActor::Fixed()
{
}

void Client::TestActor::EndPlay()
{
}

void Client::TestActor::NotifyActorBlock(Engine::CollisionData data)
{
}

void Client::TestActor::NotifyActorBeginOverlap(Engine::CollisionData data)
{
}

void Client::TestActor::NotifyActorEndOverlap(Engine::CollisionData data)
{
}

void Client::TestActor::SetupInputComponent(Engine::InputComponent* inputComponent)
{
}

void Client::TestActor::SerializeIn(nlohmann::ordered_json& object)
{
}

void Client::TestActor::SerializeOut(nlohmann::ordered_json& object)
{
}

Client::TestActor* Client::TestActor::Create()
{
    return new TestActor;
}

void Client::TestActor::Destroy()
{
	Super::Destroy();
}
