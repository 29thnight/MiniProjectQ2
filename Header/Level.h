#pragma once
#include <CoreDefine.h>

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
		virtual void Tick(_float deltaSeconds);
		virtual void Fixed();
		virtual void EndPlay();

	public:
		bool InsertActor(Actor* pActor);
		bool AddActor(Actor* pActor);
		Actor* GetActor(_pstring name);

	public:
		void SettingCamera(CameraActor* pCameraActor){ _pCameraActor = pCameraActor; }
		virtual void Destroy() override;

	private:
		ActorsList	 _actors;
		CameraActor* _pCameraActor{ nullptr };
		int			 _levelIndex{ 0 };
	};
}