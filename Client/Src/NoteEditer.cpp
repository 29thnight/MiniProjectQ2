#include "NoteEditer.h"
#include <World.h>
#include <SceneComponent.h>
#include <InputComponent.h>
#include <cassert>
#include <WinUtility.h>

#include "NoteManager.h"


void Client::NoteEditer::BeginPlay()
{
	 _pNoteManager = dynamic_cast<NoteManager*>(GetWorld()->FindActor("NoteManager"));
	 if(_pNoteManager == nullptr)
	 { 
		 assert(!"��Ʈ �Ŵ����� �����ϴ�.");
	 }

	 _pInputComponent = AddComponent<Engine::InputComponent>("InputComponent");
}

void Client::NoteEditer::Tick(_duration deltaSeconds)
{
	if (_pInputComponent->IsKeyPress(DIK_F1))
	{
		bool result = WinUtility::ShowConfirmationDialog(L"������?", L"�׽�Ʈ");
		std::cout << result << std::endl;
	}

}

void Client::NoteEditer::Fixed()
{

}

void Client::NoteEditer::EndPlay()
{

}

void Client::NoteEditer::NotifyActorBlock(Engine::CollisionData data)
{
}

void Client::NoteEditer::NotifyActorBeginOverlap(Engine::CollisionData data)
{
}

void Client::NoteEditer::NotifyActorEndOverlap(Engine::CollisionData data)
{
}

void Client::NoteEditer::SetupInputComponent(Engine::InputComponent* inputComponent)
{
	inputComponent->BindKeys(DIK_F1);


	inputComponent->AttachInputManager();
}

void Client::NoteEditer::SerializeIn(nlohmann::ordered_json& object)
{
}

void Client::NoteEditer::SerializeOut(nlohmann::ordered_json& object)
{
}
