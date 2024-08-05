#pragma once
#include <Level.h>

namespace Client
{
	class PrototypeEditerLevel : public Engine::Level
	{
	private:
		PrototypeEditerLevel() = default;
		virtual ~PrototypeEditerLevel() = default;

	public:
		// Level��(��) ���� ��ӵ�
		bool BeginPlay() override;

	public:
		static PrototypeEditerLevel* Create() { return new PrototypeEditerLevel; }

	private:

	};
};