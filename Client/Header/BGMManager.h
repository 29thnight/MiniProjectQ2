#pragma once
#include <CoreDefine.h>
#include <Actor.h>

namespace Engine
{
	CORECLASS()
}

namespace Client
{
	class BGMManager : public Engine::Actor
	{
		using Base = Engine::Actor;
	private:
		BGMManager() = default;
		virtual ~BGMManager() = default;

	public:
		virtual void BeginPlay() override;
		virtual void Tick(_duration deltaSeconds) override;
		virtual void Fixed() override;
		virtual void EndPlay() override;

	public:
		static BGMManager* Create() { return new BGMManager; }
		void Destroy() override { Actor::Destroy(); }

	private:
		std::vector<std::string> _bgmList;
		int						 _stageNumber{};
	};
}