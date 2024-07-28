#pragma once
#include <CoreDefine.h>
#include <ActorComponent.h>

namespace Engine
{
	CORECLASS()
	class StateComponent : public ActorComponent
	{
	protected:
		explicit StateComponent() = default;
		virtual ~StateComponent() = default;

	public:
		virtual bool InitializeComponent() override;
		virtual void BeginPlay() override;
		virtual void TickComponent(_float deltaSeconds) override;
		virtual void EndPlay() override;

		void AddState(int stateNumber, State* state);
		State* GetState(int stateNumber);
		void SetCurrentState(int stateNumber);
		void UpdateCurrentState(_float deltaSeconds);

		void AddTransition(int stateNumber, StateTransition* transition);
		const std::vector<StateTransition*>& GetTransitions(int stateNumber) const;

	public:
		static StateComponent* Create();
		virtual void Destroy() override;

	private:
		StateMachine* _stateMachine{ nullptr };
	};
}