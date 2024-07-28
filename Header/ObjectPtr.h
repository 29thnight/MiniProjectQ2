#pragma once 
#include <CoreBase.h>
#include <CoreDefine.h>
#include <CoreFunction.h>

namespace Engine
{
	CORECLASS()
}

template <typename T>
class ObjectPtr final
{
public:
	constexpr ObjectPtr() noexcept : _ptr(nullptr) 
	{
		static_assert(std::is_base_of<Engine::CoreBase, T>::value, "T must Has Terminate()");
	}
	constexpr ObjectPtr(std::nullptr_t) noexcept : _ptr(nullptr)
	{
		static_assert(std::is_base_of<Engine::CoreBase, T>::value, "T must Has Terminate()");
	}
	explicit ObjectPtr(T* ptr) noexcept : _ptr(ptr) 
	{ 
		static_assert(std::is_base_of<Engine::CoreBase, T>::value, "T must Has Terminate()");
		AddRef(); 
	}
	ObjectPtr(const ObjectPtr& ptr) noexcept : _ptr(ptr._ptr) 
	{ 
		static_assert(std::is_base_of<Engine::CoreBase, T>::value, "T must Has Terminate()");
		AddRef(); 
	}
	ObjectPtr(ObjectPtr&& ptr) noexcept : _ptr(std::exchange(ptr._ptr,nullptr)), _refCount(std::exchange(ptr._refCount,0)) 
	{
		static_assert(std::is_base_of<Engine::CoreBase, T>::value, "T must Has Terminate()");
	}
	~ObjectPtr() { ReleasePtr(); }

public:
	ObjectPtr& operator=(std::nullptr_t) noexcept 
	{ 
		ForceReleasePtr();
		return *this; 
	}
	ObjectPtr& operator=(T* ptr) noexcept 
	{ 
		ForceReleasePtr(ptr);
		_ptr = ptr;
		AddRef();

		return *this; 
	}
	ObjectPtr& operator=(const ObjectPtr& ptr) noexcept 
	{ 
		ForceReleasePtr(ptr._ptr);
		_ptr = ptr;
		AddRef();

		return *this; 
	}
	ObjectPtr& operator=(ObjectPtr&& ptr) noexcept 
	{ 
		std::exchange(ptr._ptr,nullptr);
		std::exchange(ptr._refCount,0);

		return *this; 
	}

public:
	T* operator->() const noexcept { return _ptr; }
	T& operator*() const noexcept { return *_ptr; }
	operator bool() const noexcept { return _ptr != nullptr; }

public:
	bool operator==(const ObjectPtr& ptr) const noexcept { return _ptr == ptr._ptr; }

public:
	T* Get() const noexcept { return _ptr; }
	long GetRefCount() const noexcept { return _refCount; }

private:
	void ForceReleasePtr(T* ptr = nullptr) noexcept
	{
		SafeDelete(_ptr);
	}

	void ReleasePtr() noexcept
	{
		if (0 < _refCount)
			_refCount--;

		if(!_refCount)
			ForceReleasePtr();
	}

	void AddRef() noexcept
	{
		_refCount++;
	}

private:
	T*	 _ptr{ nullptr };
	long _refCount{ 0 };
};

template <typename T>
inline ObjectPtr<T> MakeObjectPtr()
{
	static_assert(std::is_base_of<Engine::CoreBase, T>::value, "T must Has Terminate()");
	return ObjectPtr<T>();
}

template <typename T, typename U>
inline ObjectPtr<T> MakeObjectPtr(U* ptr)
{
	static_assert(std::is_base_of<Engine::CoreBase, T>::value, "T must Has Terminate()");
	static_assert(std::is_base_of<Engine::CoreBase, T>::value, "T must Has Terminate()");
	return ObjectPtr<T>(ptr);
}

template <typename T>
inline ObjectPtr<T> MakeObjectPtr(const ObjectPtr<T>& ptr)
{
	static_assert(std::is_base_of<Engine::CoreBase, T>::value, "T must Has Terminate()");
	return ObjectPtr<T>(ptr);
}

template <typename T>
inline ObjectPtr<T> MakeObjectPtr(ObjectPtr<T>&& ptr)
{
	static_assert(std::is_base_of<Engine::CoreBase, T>::value, "T must Has Terminate()");
	return ObjectPtr<T>(std::move(ptr));
}