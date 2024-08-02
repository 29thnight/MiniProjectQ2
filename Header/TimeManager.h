#pragma once
#include <CoreDefine.h>
#include <Singleton.h>

namespace Engine
{
	class TimeManager : public CoreBase, public Singleton<TimeManager>
	{
	private:
		friend class Singleton;

	private:
		TimeManager() = default;
		~TimeManager() = default;

	public:
		using _clock = std::chrono::high_resolution_clock;
		using _duration = std::chrono::duration<std::chrono::nanoseconds>;
		using _timePoint = std::chrono::high_resolution_clock::time_point;

	public:
		bool Initialize();
		void UpdateTick();
		void SetTimeScale(_float timeScale);

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) {};
		virtual void SerializeOut(nlohmann::ordered_json& object) {};

	public:
		ReadOnly_Property(std::chrono::nanoseconds, DeltaSeconds)
		_Get(DeltaSeconds)
		{
			return GetDeltaSeconds();
		}

		WriteOnly_Property(_float, TimeScale)
		_Set(TimeScale)
		{
			_timeScale = value;
		}

	public:
		int GetFPS() const;
		std::chrono::nanoseconds GetDeltaSeconds() const;
		std::chrono::nanoseconds GetTimeScale() const;

	private:
		void Destroy() override;

	private:
		_timePoint _prevTick{};
		std::chrono::nanoseconds _deltaSeconds{ 0.f };
		std::chrono::nanoseconds _timeScale{ 1.0f };
	};
}

inline Engine::TimeManager* Time = Engine::TimeManager::GetInstance();
inline std::function<void()> TimeTerminate = []() { Time->Terminate(); };