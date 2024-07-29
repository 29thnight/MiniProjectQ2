#pragma once
#include <CoreDefine.h>
#include <ActorComponent.h>
#include <IOnInputReceived.h>
#include <InputMapping.h>
#include <ISetupInputComponent.h>

namespace Engine
{
	CORECLASS()
	class InputComponent : public ActorComponent, public IOnInputReceived
	{
	protected:
		explicit InputComponent() = default;
		virtual ~InputComponent() = default;

	protected:
		using BindFunction = std::function<void(const InputActionValue&)>;
		using InputActions = std::tuple<IInputAction*, TriggerEvent, void*>;
		struct CompareInputKey
		{
			bool operator()(const InputActions& lhs, const InputActions& rhs) const
			{
				if (std::get<0>(lhs) != std::get<0>(rhs)) return std::get<0>(lhs) < std::get<0>(rhs);
				if (std::get<1>(lhs) != std::get<1>(rhs)) return std::get<1>(lhs) < std::get<1>(rhs);
				return std::get<2>(lhs) < std::get<2>(rhs);
			}
		};
		using InputActionsMap = std::map<IInputAction*, BindFunction, CompareInputKey>;
		using InputEvents = std::deque<InputValue>;
		using MapUniqueKey = std::vector<std::pair<_uint,InputComponent*>>;


	public:
		virtual bool InitializeComponent() override;
		virtual void BeginPlay() override { };
		virtual void TickComponent(_float deltaSeconds) override;
		virtual void EndPlay() override {};
		virtual void OnInputReceived(const InputValue& value) override;

	public:
		void BindKey(_uint key);
		void SetInputMapping(InputMapping* inputMapping);
		void AttachInputManager();
		void SetVibration(_float leftMotor, _float rightMotor, _float duration);

	public:
		bool IsKeyPress(_uint key) const;
		bool IsKeyHold(_uint key) const;
		bool IsKeyRelease(_uint key) const;

	public:
		bool IsKeyEventTriggerNow(_uint key, InputType type) const;
		bool IsKeyEventTriggered(_uint key, InputType type) const;
		bool IsLastInputOverTime(_float time) const;
		bool IsKeyEventTriggeredOverTime(_uint key, InputType type, _float time) const;
		bool IsKeyEventTriggeredLessTime(_uint key, InputType type, _float time) const;

	public:
		template<typename... _uint>
		void BindKeys(_uint... keys)
		{
			(_uniqueKey.emplace_back(std::make_pair(keys, this)), ...);
		}

		template<typename T, typename U>
		void BindAction(const IInputAction* action, TriggerEvent event, T* object, void (U::*method)(const InputActionValue&))
		{
			BindFunction function = [object, method](const InputActionValue& value)
            {
                (object->*method)(value);
            };
            _inputActions[std::make_tuple(action, event, static_cast<void*>(object))] = function;
		}

		void TriggerAction(IInputAction* action, TriggerEvent event, const InputActionValue& value);

	public:
		static InputComponent* Create();

	protected:
		virtual void Destroy() override;

	protected:
		InputActionsMap	_inputActions;
		InputEvents		_inputEvents;
		MapUniqueKey	_uniqueKey;
		InputMapping*	_inputMapping{ nullptr };

	protected:
		float elapsedTick{ 0.f };
	};
}