#pragma once
#include <BitmapComponent.h>

namespace Engine
{
	CORECLASS()
	class AnimationComponent : public BitmapComponent
	{
	protected:
		explicit AnimationComponent() = default;
		virtual ~AnimationComponent() = default;

	public:
		virtual void TickComponent(_float deltaSeconds) override;
		virtual void Render(_RenderTarget pRenderTarget) override;
		void AddClip(_pstring clipName, _float frameTime, bool isLoop = false);
		const bool IsClipPlay(_pstring clipName) const;
		const bool IsClipEnd(_pstring clipName) const;
		const bool IsFrameEnd() const;
		void SetPlayClip(_pstring clipName);
		void RemoveClip(_pstring clipName);
		
	protected:
		virtual bool InitializeComponent() override;
		virtual void Destroy() override;

	public:
		static AnimationComponent* Create();

	private:
		std::unordered_map<_pstring, AnimationClip*> _vecClips;
		_pstring _currentClipName{};
		float	 _frameTime{ 0 };
		float	 _currentFrameTime{ -1 };
		int		 _prevFrame{ -1 };
		int		 _currentFrame{ -1 };
		int		 _frameCount{ -1 };
		int		 _currentClipIndex{ -1 };
		bool	 _isLoop{ false };
		bool     _isInLayer{ false };
		bool     _isFrameEnd{ false };
	};
}