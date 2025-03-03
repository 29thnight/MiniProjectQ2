#include "PrototypeEditerLevel.h"
#include "NoteManager.h"
#include "NoteEditer.h"

#include <SceneComponent.h>

using Vector2 = Mathf::Vector2;

bool Client::PrototypeEditerLevel::BeginPlay()
{
	SpawnActor(LAYER::OBJECT, "NoteManager", NoteManager::Create(), Vector2(500.f, 500.f));
	SpawnActor(LAYER::OBJECT, "NoteEditer", NoteEditer::Create(), Vector2(500.f, 500.f));

	return true;
}
