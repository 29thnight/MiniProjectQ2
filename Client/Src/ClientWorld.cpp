#include <ClientWorld.h>
#include <ClientLevel.h>
#include <Level.h>

bool Client::ClientWorld::BeginPlay()
{
	//Engine::Level* pLevel = ClientLevel::Create();
	//ContainLevel(pLevel);
	//pLevel->BeginPlay();

	AddLevel<ClientLevel>();

	SettingCamera();

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
