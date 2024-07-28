#include <TimeManager.h>

constexpr float immediate{ 0.001f };

bool Engine::TimeManager::Initialize()
{
	_prevTick = _clock::now();

	return true;
}

void Engine::TimeManager::UpdateTick()
{
	auto currentTick = _clock::now();
	_duration duration = currentTick - _prevTick;
	_deltaSeconds = duration.count() * _timeScale;
	_prevTick = currentTick;
}

void Engine::TimeManager::SetTimeScale(_float timeScale)
{
	_timeScale = timeScale;
}

int Engine::TimeManager::GetFPS() const
{
	return static_cast<int>(round(1.f / _deltaSeconds));
}

_float Engine::TimeManager::GetDeltaSeconds() const
{
	if (100.f < _deltaSeconds)
		return immediate;

	return _deltaSeconds;
}

_float Engine::TimeManager::GetTimeScale() const
{
	return _timeScale;
}

void Engine::TimeManager::Destroy()
{
}
