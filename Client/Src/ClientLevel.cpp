#include "ClientLevel.h"
#include "TestActor.h"

bool Client::ClientLevel::BeginPlay()
{
	SpawnActor(LAYER::OBJECT,"TestActor",TestActor::Create(),Mathf::Vector2{500.f, 500.f});

	return true;
}
