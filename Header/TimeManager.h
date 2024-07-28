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
		using _duration = std::chrono::duration<float>;
		using _timePoint = std::chrono::high_resolution_clock::time_point;

	public:
		bool Initialize();
		void UpdateTick();
		void SetTimeScale(_float timeScale);

	public:
		ReadOnly_Property(_float, DeltaSeconds)
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
		_float GetDeltaSeconds() const;
		_float GetTimeScale() const;

	private:
		void Destroy() override;

	private:
		_timePoint _prevTick{};
		float _deltaSeconds{ 0.f };
		float _timeScale{ 1.0f };
	};
}

inline Engine::TimeManager* Time = Engine::TimeManager::GetInstance();
inline std::function<void()> TimeTerminate = []() { Time->Terminate(); };