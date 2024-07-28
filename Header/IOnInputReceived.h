#pragma once
#include <CoreDefine.h>

namespace Engine
{
	interface IOnInputReceived
	{
		virtual void OnInputReceived(const InputValue& inputEvent) abstract;
	};
}