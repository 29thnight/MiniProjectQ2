#include <ClientWorld.h>
#include <ClientLevel.h>
#include <TestActor.h>
#include <Level.h>

bool Client::ClientWorld::BeginPlay()
{
	AddLevel<ClientLevel>();

	SpawnActor(LAYER::OBJECT,"TestActor",TestActor::Create(),Mathf::Vector2{700.f, 700.f});

	SettingCamera();
	SettingTrackingCameraTarget(FindActor("TestActor"));

	return isBeginPlayEnd;
}

Client::ClientWorld* Client::ClientWorld::Create()
{
	return new ClientWorld();
}

void Client::ClientWorld::Destroy()
{
	Super::Destroy();
}
