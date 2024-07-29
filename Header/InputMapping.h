#pragma once
#include <CoreDefine.h>
#include <IInputAction.h>
#include <Mathf.h>

namespace Engine
{
	CORECLASS()
	class InputMapping abstract : public CoreBase
	{
	protected:
		explicit InputMapping() = default;
		virtual ~InputMapping() = default;

	public:
		virtual void KeyMapping() abstract;
		virtual void MappingContext(const InputValue& inputEvent) abstract;

	public:
		void Contain(IInputAction* inputAction){ _actions.push_back(inputAction); }
		void SetTarget(Actor* target) { _target = target; }
		void SetPriority(int priority) { _priority = priority; }
		IInputAction* GetCurrentAction() const { return _currentAction; }
		void SetInputComponent(InputComponent* inputComponent) { _inputComponent = inputComponent; }

		void ChangeAction(IInputAction* inputAction);
		void CompareAndTriggerAction(_uint key, InputType type, _float deltaSeconds);
		void Destroy() override;

	protected:
		Actor*	_target{ nullptr };
		int		_priority{ 0 };
		IInputAction* _currentAction{ nullptr };
		InputComponent* _inputComponent{ nullptr };
		std::vector<IInputAction*> _actions;
	};
}