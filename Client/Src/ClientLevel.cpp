#include "ClientLevel.h"
#include "TestActor.h"

bool Client::ClientLevel::BeginPlay()
{
	SpawnActor(LAYER::OBJECT,"TestActor",TestActor::Create(),Mathf::Vector2{700.f, 700.f});

	return true;
}
