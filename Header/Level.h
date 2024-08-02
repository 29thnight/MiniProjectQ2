#pragma once
#include <CoreDefine.h>
#include <Mathf.h>

namespace Engine
{
	CORECLASS()
	class Level : public CoreBase
	{
	private:
		using ActorsList = std::list<Actor*>;

	protected:
		Level() = default;
		~Level() = default;

	public:
		virtual bool BeginPlay() PURE;
		virtual void Tick(_duration deltaSeconds);
		virtual void Fixed();
		virtual void EndPlay();

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) {};
		virtual void SerializeOut(nlohmann::ordered_json& object) {};

	public:
		void SetWorld(World* pWorld) { _pWorld = pWorld; }
		bool InsertActor(Actor* pActor);
		bool AddActor(Actor* pActor);
		Actor* GetActor(_pstring name);
		bool SpawnActor(int layerIndex, _pstring name, Actor* pActor);
		bool SpawnActor(int layerIndex, _pstring name, Actor* pActor, Mathf::Vector2 location);
		bool RemoveActor(_pstring name);
		bool TerminateActor(_pstring name);
		bool ReviveActor(_pstring name);

	public:
		void SettingLevelCamera(CameraActor* pCameraActor){ _pCameraActor = pCameraActor; }
		virtual void Destroy() override;

	private:
		ActorsList	 _actors;
		World*		 _pWorld{ nullptr };
		CameraActor* _pCameraActor{ nullptr };
		int			 _levelIndex{ 0 };
	};
}