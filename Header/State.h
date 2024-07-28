#pragma once
#include <CoreBase.h>
#include <CoreDefine.h>
#include <Delegate.h>

namespace Engine
{
	CORECLASS()
	class State abstract : public CoreBase
	{
	protected:
		explicit State() = default;
		virtual ~State() = default;

	public:
		virtual void Destroy() override {}

		void OnEnterState();
		void OnUpdateState(_float deltaSeconds);
		void OnExitState();

		void SetOwner(Actor* owner) { pOwner = owner; }
		void SetStateID(int id) { stateID = id; }

		Actor* GetOwner() const { return pOwner; }
		int GetStateID() const { return stateID; }

		void AddTransition(StateTransition* transition) { _transitions.push_back(transition); }
		const std::vector<StateTransition*>& GetTransitions() const { return _transitions; }

	public:
		Delegate<>		 OnEnter;
		Delegate<_float> OnUpdate;
		Delegate<>       OnExit;

	private:
		std::vector<StateTransition*> _transitions;
		Actor*	pOwner{ nullptr };
		int		stateID{ 0 };
	};
}