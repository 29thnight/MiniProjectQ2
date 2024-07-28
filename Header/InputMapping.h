#pragma once
#include <CoreDefine.h>
#include <IInputAction.h>
#include <Mathf.h>

namespace Engine
{
	CORECLASS()
	class InputMapping abstract : public CoreBase
	{
	private:
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

		void ChangeAction(IInputAction* inputAction)
		{
			if (_currentAction != nullptr)
			{
				_currentAction->Completed();
			}

			_currentAction = inputAction;
			_currentAction->Entered();
		}

	private:
		Actor*	_target{ nullptr };
		int		_priority{ 0 };
		IInputAction* _currentAction{ nullptr };
		std::vector<IInputAction*> _actions;
	};
}