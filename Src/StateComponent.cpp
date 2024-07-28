#include <StateComponent.h>
#include <StateMachine.h>
#include <State.h>
#include <StateTransition.h>

bool Engine::StateComponent::InitializeComponent()
{
	_stateMachine = StateMachine::Create();

    return true;
}

void Engine::StateComponent::BeginPlay()
{
}

void Engine::StateComponent::TickComponent(_float deltaSeconds)
{
	_stateMachine->UpdateCurrentState(deltaSeconds);
}

void Engine::StateComponent::EndPlay()
{
}

void Engine::StateComponent::AddState(int stateNumber, State* state)
{
	_stateMachine->AddState(stateNumber, state);
}

Engine::State* Engine::StateComponent::GetState(int stateNumber)
{
	return _stateMachine->GetState(stateNumber);
}

void Engine::StateComponent::SetCurrentState(int stateNumber)
{
	_stateMachine->SetCurrentState(stateNumber);
}

void Engine::StateComponent::UpdateCurrentState(_float deltaSeconds)
{
	_stateMachine->UpdateCurrentState(deltaSeconds);
}

void Engine::StateComponent::AddTransition(int stateNumber, StateTransition* transition)
{
	_stateMachine->GetState(stateNumber)->AddTransition(transition);
}

const std::vector<Engine::StateTransition*>& Engine::StateComponent::GetTransitions(int stateNumber) const
{
	return _stateMachine->GetState(stateNumber)->GetTransitions();
}

Engine::StateComponent* Engine::StateComponent::Create()
{
	StateComponent* pInstance = new StateComponent();
	if (pInstance->InitializeComponent())
		return pInstance;

	SafeDelete(pInstance);
	return nullptr;
}

void Engine::StateComponent::Destroy()
{
	SafeDelete(_stateMachine);
}
