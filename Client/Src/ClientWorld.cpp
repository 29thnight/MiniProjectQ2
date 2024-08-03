#include <ClientWorld.h>
#include <ClientLevel.h>
#include <Level.h>

bool Client::ClientWorld::BeginPlay()
{
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
