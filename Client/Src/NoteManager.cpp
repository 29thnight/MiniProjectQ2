#include <NoteManager.h>
#include <SceneComponent.h>
#include <SoundManager.h>
#include <InputComponent.h>
#include <CsvLoader.h>
#include <World.h>

using namespace Engine;

void Client::NoteManager::BeginPlay()
{
	Base::BeginPlay();
	Sound->PlaySound("Mario64_Main_Theme", CHANNEL_BGM, NOT_LOOP);
	std::cout << Sound->GetLength(CHANNEL_BGM) << std::endl;

	CSVReader<int, long double> reader("Assets/test.csv");
	reader.forEach([&](int noteIndex, long double noteTime)
		{
			NoteSpwanTable table;
			table._noteIndex = noteIndex;
			table._noteTime = noteTime;
			_noteSpawnData.push_back(table);
		});

	_pInputComponent = AddComponent<InputComponent>("InputComponent");

}

void Client::NoteManager::Tick(_duration deltaSeconds)
{
	Base::Tick(deltaSeconds);

	//std::cout << Sound->GetPosition(CHANNEL_BGM) << std::endl;
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
	inputComponent->BindKeys(DIK_SPACE, DIK_LEFT, DIK_RIGHT);
	inputComponent->AttachInputManager();
}

void Client::NoteManager::SerializeIn(nlohmann::ordered_json& object)
{
}

void Client::NoteManager::SerializeOut(nlohmann::ordered_json& object)
{
}
