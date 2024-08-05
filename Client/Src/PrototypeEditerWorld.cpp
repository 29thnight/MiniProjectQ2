#include <PrototypeEditerWorld.h>
#include <Level.h>
#include <PrototypeEditerLevel.h>

bool Client::PrototypeEditerWorld::BeginPlay()
{
	AddLevel<PrototypeEditerLevel>();
	SettingCamera();

	return isBeginPlayEnd;
}


Client::PrototypeEditerWorld* Client::PrototypeEditerWorld::Create()
{
	return new PrototypeEditerWorld();
}

void Client::PrototypeEditerWorld::Destroy()
{
	Super::Destroy();
}
