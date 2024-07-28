#pragma once
#include <CoreDefine.h>
#include <ActorComponent.h>
#include <IOnInputReceived.h>
#include <InputMapping.h>

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
		using InputActions = std::unordered_map<const IInputAction*, std::unordered_map<TriggerEvent, std::pair<Object*,BindFunction>>>;
		using InputEvents = std::deque<InputValue>;
		using MapUniqueKey = std::vector<std::pair<_uint,InputComponent*>>;

	public:
		virtual bool InitializeComponent() override { return true; }
		virtual void BeginPlay() override {};
		virtual void TickComponent(_float deltaSeconds) override;
		virtual void EndPlay() override {};
		virtual void OnInputReceived(const InputValue& value) override;

	public:
		void BindKey(_uint key);
		void SetInputMapping(InputMapping* inputMapping) { _inputMapping = inputMapping; }
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
		template<typename T, typename U>
		void BindAction(const IInputAction*, TriggerEvent, T* Object, void (U::*method)(const InputActionValue&))
		{
			BindFunction function = [Object, method](const InputActionValue& value) { (Object->*method)(value); };
			_inputActions.emplace(IInputAction, TriggerEvent, Object, function);
		}

	public:
		static InputComponent* Create();

	protected:
		virtual void Destroy() override;

	protected:
		InputActions	_inputActions;
		InputEvents		_inputEvents;
		MapUniqueKey	_uniqueKey;
		InputMapping*	_inputMapping{ nullptr };

	protected:
		float elapsedTick{ 0.f };
	};
}