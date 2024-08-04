#include "TestActor.h"
#include <AnimationComponent.h>
#include <InputComponent.h>
#include <SoundManager.h>

void Client::TestActor::BeginPlay()
{
	_pAnimationComponent = AddComponent<Engine::AnimationComponent>("AnimationComponent");
	_pAnimationComponent->SetPlayClip("Idle"); //그런데 얘 테스트용이라 용량크거든? 조심해라?

	_pInputComponent = AddComponent<Engine::InputComponent>("InputComponent");
}

void Client::TestActor::Tick(_duration deltaSeconds)
{
	Super::Tick(deltaSeconds);

	if(_pInputComponent->IsKeyPress(DIK_SPACE))
	{
		Sound->LoopExit(CHANNEL_BGM, LOOP_ONCE);
		std::cout << "Space Key Pressed Pos : " << Sound->GetPosition(CHANNEL_BGM) << std::endl;
	}

	if(20000 <= Sound->GetPosition(CHANNEL_BGM) && 25000 > Sound->GetPosition(CHANNEL_BGM))
	{
		Sound->LoopEnter(CHANNEL_BGM, 25000, 30000);
	}
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
	inputComponent->BindKeys(DIK_SPACE, DIK_LEFT, DIK_RIGHT);
	inputComponent->AttachInputManager();
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
