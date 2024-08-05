#pragma once
#include <Actor.h>

namespace Engine
{
	CORECLASS()
}

namespace Client
{
	class NoteManager;

	class NoteEditer : public Engine::Actor
	{
	private:
		NoteEditer() = default;
		virtual ~NoteEditer() = default;

	public:
		virtual void BeginPlay() override;
		virtual void Tick(_duration deltaSeconds) override;
		virtual void Fixed() override;
		virtual void EndPlay() override;

	public:
		virtual void NotifyActorBlock(Engine::CollisionData data) override;
		virtual void NotifyActorBeginOverlap(Engine::CollisionData data) override;
		virtual void NotifyActorEndOverlap(Engine::CollisionData data) override;

	public:
		virtual void SetupInputComponent(Engine::InputComponent* inputComponent) override;

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) override;
		virtual void SerializeOut(nlohmann::ordered_json& object) override;

	public:
		static NoteEditer* Create() { return new NoteEditer; }
		void Destroy() override { Actor::Destroy(); }

	private:
		NoteManager* _pNoteManager = nullptr;
		Engine::InputComponent* _pInputComponent = nullptr;

	};
}