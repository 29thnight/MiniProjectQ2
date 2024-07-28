#pragma once
#include <CoreDefine.h>

namespace Engine
{
	CORECLASS()
	class Layer : public CoreBase
	{
	private:
		using RenderQueue = std::deque<RenderComponent*>;

	private:
		Layer() = default;
		~Layer() = default;

	public:
		void Render(_RenderTarget pRenderTarget);

	public:
		void AddRenderQueue(RenderComponent* pRenderComponent);
		void RemoveRenderQueue(RenderComponent* pRenderComponent);

	public:
		static Layer* InitializeLayer(int index);
		void SettingCamera(CameraActor* pCameraActor){ _pCameraActor = pCameraActor; }
		void Destroy() override;

	private:
		RenderQueue	 _renderQueue;
		CameraActor* _pCameraActor{ nullptr };
		int			 _layerIndex{ 0 };
	};
}