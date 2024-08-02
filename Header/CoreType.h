#pragma once
#include <CoreDefine.h>
#include <cstddef>

typedef unsigned char			_byte;
typedef unsigned short			_ushort;
typedef unsigned int			_uint;
typedef unsigned long			_ulong;
typedef unsigned long long		_ullong;
typedef const int&				_int;
typedef const float&			_float;
typedef const char*				_pstring;
typedef const wchar_t*			_pwstring;
typedef IDWriteTextFormat		_FontFormat;
typedef IDWriteTextFormat*		_pFontFormat;
typedef ID2D1RenderTarget*		_RenderTarget;
typedef ID2D1SolidColorBrush*	Brush;
typedef _bstr_t					string;
typedef D2D1::ColorF			Color;

using _duration = std::chrono::nanoseconds;

//template<typename ComType>
//using SmartPtr = Microsoft::WRL::ComPtr<ComType>;
template<typename ComType>
class SmartPtr : public Microsoft::WRL::ComPtr<ComType>
{
public:
	SmartPtr() = default;
	SmartPtr(ComType* ptr) : Microsoft::WRL::ComPtr<ComType>(ptr) {}
	SmartPtr(const Microsoft::WRL::ComPtr<ComType>& ptr) : Microsoft::WRL::ComPtr<ComType>(ptr) {}
	SmartPtr(Microsoft::WRL::ComPtr<ComType>&& ptr) noexcept : Microsoft::WRL::ComPtr<ComType>(std::move(ptr)) {}

	ComType* operator->() const { return this->Get(); }
	ComType* Get() const { return Microsoft::WRL::ComPtr<ComType>::Get(); }
};


#undef ChooseColor
inline Color ChooseColor(Palette color)
{
	return Color(color);
}

       