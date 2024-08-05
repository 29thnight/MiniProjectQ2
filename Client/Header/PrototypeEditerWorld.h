#pragma once
#include <World.h>

namespace Client
{
	class PrototypeEditerWorld : public Engine::World
	{
	private:
		PrototypeEditerWorld() = default;
		virtual ~PrototypeEditerWorld() = default;

	public:
		bool BeginPlay() override;

	public:
		static PrototypeEditerWorld* Create();
		void Destroy() override;
	};
}