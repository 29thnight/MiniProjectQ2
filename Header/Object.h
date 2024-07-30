#pragma once
#include <CoreDefine.h>
#include <CoreBase.h>

namespace Engine
{
	class Object abstract : public CoreBase
	{
	protected:
		explicit Object() = default;
		virtual ~Object() = default;

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) {};
		virtual void SerializeOut(nlohmann::ordered_json& object) {};

	public:
		_uint GetInstanceID() const { return _instanceID; }
		_pstring GetName() const { return _name; }
		void SetName(_pstring name) { _name = name; }

	public:
		void OnCompleteDestroyMark() { _isMark = true; _isCompleteDestroy = true; }
		void OnDestroyMark() { _isMark = true; }
		void OnRevive() { _isMark = false; }
		bool IsDestroyMarked() const { return _isMark; }
		bool IsCompleteDestroyMarked() const { return _isCompleteDestroy; }
		void CreateObjectDirectory();

	protected:
		virtual void Destroy() override abstract;

	protected:
		_pstring _name{ nullptr };

	private:
		static _uint ID;

	private:
		_uint _instanceID{ 0 };
		bool  _isMark{ false };
		bool  _isCompleteDestroy{ false };
	};
}