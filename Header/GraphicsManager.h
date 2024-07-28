#pragma once
#include <CoreDefine.h>
#include <Singleton.h>

namespace Engine
{
	class GraphicsManager : public CoreBase, public Singleton<GraphicsManager>
	{
	private:
		friend class Singleton;

	private:
		using BrushContainer = std::unordered_map<_pstring, SmartPtr<ID2D1SolidColorBrush>>;

	private:
		explicit GraphicsManager() = default;
		virtual ~GraphicsManager() = default;

	public:
		HRESULT Initialize();
		HRESULT AddBrush(_pstring brushName, const Color& color);
		ID2D1SolidColorBrush* GetBrush(_pstring brushName);

	public:
		void Destroy() override;

	private:
		HRESULT InitializeD2D(HWND hWnd);

	private:
		IWICImagingFactory*				_pWICFactory{};
		SmartPtr<ID2D1Factory>			_pD2DFactory{};
		SmartPtr<ID2D1HwndRenderTarget>	_pRenderTarget{};
		BrushContainer					_solidBrush{};
	};
}

inline Engine::GraphicsManager* Graphics = Engine::GraphicsManager::GetInstance();
inline std::function<void()> GraphicsTerminate = []() { Graphics->Terminate(); };