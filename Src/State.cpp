#include <State.h>
#include <Delegate.h>

void Engine::State::OnEnterState()
{
	OnEnter.Broadcast();
}

void Engine::State::OnUpdateState(_float deltaSeconds)
{
	OnUpdate.Broadcast(deltaSeconds);
}

void Engine::State::OnExitState()
{
	OnExit.Broadcast();
}
