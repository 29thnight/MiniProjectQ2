#include <CoreDefine.h>
#include <InputManager.h>
#include <InputComponent.h>
#include <Actor.h>

bool Engine::InputComponent::InitializeComponent()
{
	_owner->SetupInputComponent(this);

	return true;
}

void Engine::InputComponent::TickComponent(_float deltaSeconds)
{
	if (_inputEvents.empty())
		return;

	if (_inputMapping)
	{
		_inputMapping->GetCurrentAction()->Triggers(deltaSeconds);
	}

	if (9999.f > elapsedTick)
	{
		elapsedTick += deltaSeconds;
	}
}

void Engine::InputComponent::OnInputReceived(const InputValue& value)
{
	if (_owner->IsDestroyMarked())
		return;

	if (!_inputEvents.empty())
	{
		_inputEvents.back().timeToLastInput = elapsedTick;
	}

	elapsedTick = 0.f;

	_inputEvents.emplace_back(value);

	if (_inputMapping)
	_inputMapping->MappingContext(value);

	if(_inputEvents.size() > 30)
	{
		_inputEvents.pop_front();
	}
}

void Engine::InputComponent::BindKey(_uint key)
{
	_uniqueKey.emplace_back(std::make_pair(key, this));
}

void Engine::InputComponent::SetInputMapping(InputMapping* inputMapping)
{
	_inputMapping = inputMapping;
	_inputMapping->SetInputComponent(this);
}

void Engine::InputComponent::AttachInputManager()
{
	for (auto& key : _uniqueKey)
	{
		InputMgr->RegisterComponent(key.first, key.second);
	}
}

void Engine::InputComponent::SetVibration(_float leftMotor, _float rightMotor, _float duration)
{
	XINPUT_VIBRATION vibration
	{
		static_cast<WORD>(leftMotor * USHRT_MAX),
		static_cast<WORD>(rightMotor * USHRT_MAX)
	};

	XInputSetState(0, &vibration);
}

bool Engine::InputComponent::IsKeyPress(_uint key) const
{
	if (_inputEvents.empty())
		return false;

	return (_inputEvents.back().key == key && 
			_inputEvents.back().type == InputType::PRESS &&
			0.f == _inputEvents.back().timeToLastInput);
}

bool Engine::InputComponent::IsKeyHold(_uint key) const
{
	if (_inputEvents.empty())
		return false;

	return (_inputEvents.back().key == key && 
			_inputEvents.back().type == InputType::HELD &&
			0.f == _inputEvents.back().timeToLastInput);
}

bool Engine::InputComponent::IsKeyRelease(_uint key) const
{
	if (_inputEvents.empty())
		return false;

	return (_inputEvents.back().key == key && 
			_inputEvents.back().type == InputType::RELEASE &&
			0.f == _inputEvents.back().timeToLastInput);
}

bool Engine::InputComponent::IsKeyEventTriggerNow(_uint key, InputType type) const
{
	if (_inputEvents.empty())
		return false;

	if (_inputEvents.back().timeToLastInput > 0.f)
		return false;

	if (_inputEvents.back().key == key && _inputEvents.back().type == type)
	{
		return true;
	}

	return false;
}

bool Engine::InputComponent::IsKeyEventTriggered(_uint key, InputType type) const
{
	if (_inputEvents.empty())
		return false;

	for (auto& inputEvent : _inputEvents)
	{
		if (inputEvent.key == key && inputEvent.type == type)
			return true;
	}

	return false;
}

bool Engine::InputComponent::IsLastInputOverTime(_float time) const
{
	if (_inputEvents.empty())
		return false;

	if (0.f == _inputEvents.back().timeToLastInput && elapsedTick > time)
	{
		return true;
	}

	return false;
}

bool Engine::InputComponent::IsKeyEventTriggeredOverTime(_uint key, InputType type, _float time) const
{
	if (_inputEvents.empty())
		return false;

	for (auto iter = _inputEvents.rbegin();
		iter != _inputEvents.rend(); iter++)
	{
		if (iter->key == key && iter->type == type)
		{
			return elapsedTick > time;
		}
	}

	return false;
}

bool Engine::InputComponent::IsKeyEventTriggeredLessTime(_uint key, InputType type, _float time) const
{
	if (_inputEvents.empty())
		return false;

	for (auto iter = _inputEvents.rbegin();
		iter != _inputEvents.rend(); iter++)
	{
		if (iter->key == key && iter->type == type)
		{
			return elapsedTick < time;
		}
	}

	return false;
}

void Engine::InputComponent::TriggerAction(IInputAction* action, TriggerEvent event, const InputActionValue& value)
{
	for (auto& [key, function] : _inputActions) 
    {
		std::tuple<IInputAction*, TriggerEvent, void*> key = key;
        if (std::get<0>(key) == action && std::get<1>(key) == event)
        {
            function(value);
        }
    }
}

Engine::InputComponent* Engine::InputComponent::Create()
{
	return new InputComponent;
}

void Engine::InputComponent::Destroy()
{
	for (auto& key : _uniqueKey)
	{
		InputMgr->UnRegisterComponent(key.first, key.second);
	}

	_uniqueKey.clear();
	_inputActions.clear();
	_inputEvents.clear();
	_inputMapping = nullptr;
	elapsedTick = 0.f;
}
