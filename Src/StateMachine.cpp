#include <StateMachine.h>
#include <State.h>
#include <StateTransition.h>

void Engine::StateMachine::AddState(int stateNumber, State* state)
{
	state->SetStateID(stateNumber);
	states[stateNumber] = state;
}

Engine::State* Engine::StateMachine::GetState(int index)
{
    return states[index];
}

void Engine::StateMachine::SetCurrentState(int index)
{
    if (currentState != nullptr) 
    {
        currentState->OnExitState();
    }
    currentState = GetState(index);
    if (currentState != nullptr) 
    {
        currentState->OnEnterState();
    }
}

void Engine::StateMachine::UpdateCurrentState(_float deltaSeconds)
{
    if (currentState != nullptr) 
    {
        currentState->OnUpdateState(deltaSeconds);
        CheckTransitions();
    }
}

void Engine::StateMachine::Destroy()
{
	for (auto state : states)
	{
		SafeDelete(state.second);
	}
	states.clear();
	currentState = nullptr;
}

void Engine::StateMachine::CheckTransitions()
{
    for (auto transition : currentState->GetTransitions()) 
    {
        if (transition->CanTransition()) 
        {
            SetCurrentState(transition->GetNextState());
            break;
        }
    }
}

void Engine::StateMachine::SetCurrentState(State* state)
{
    if (currentState != nullptr) 
    {
        currentState->OnExitState();
    }
    currentState = state;
    if (currentState != nullptr) 
    {
        currentState->OnEnterState();
    }
}
