#pragma once

namespace Engine
{
	class CoreBase abstract
	{
	protected:
		explicit CoreBase() = default;
		virtual ~CoreBase() = default;

	public:
		virtual void Terminate()
		{
			Destroy();
			delete this; 
		}

	protected:
		virtual void Destroy() abstract;
	};
}