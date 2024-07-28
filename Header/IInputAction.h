#pragma once
#include <CoreDefine.h>

namespace Engine
{
	interface IInputAction
	{
		virtual void Entered() abstract;
		virtual void Triggers(_float deltaSeconds) abstract;
		virtual void Completed() abstract;
	};
}