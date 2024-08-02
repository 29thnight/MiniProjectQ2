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
		virtual bool InitializeComponent() override;
		virtual void TickComponent(_duration deltaSeconds) override;
		virtual void Render(_RenderTarget pRenderTarget) override;
		void SetAnimationRect(Animation* pAnimation);
		void AllAddClipThisActor();
		void AddClip(_pstring clipName, _float frameTime, bool isLoop = false);
		const bool IsClipPlay(_pstring clipName) const;
		const bool IsClipEnd(_pstring clipName) const;
		const bool IsFrameEnd() const;
		void SetPlayClip(_pstring clipName);
		void RemoveClip(_pstring clipName);

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) {};
		virtual void SerializeOut(nlohmann::ordered_json& object) {};
		
	protected:
		virtual void Destroy() override;

	public:
		static AnimationComponent* Create();

	private:
		std::unordered_map<std::string, AnimationClip*> _vecClips;

	private:
		_pstring _currentClipName{};

	private:
		float	 _frameTime{ 0 };
		float	 _currentFrameTime{ -1 };

	private:
		int		 _indexCount{ 0 };
		int		 _prevFrame{ -1 };
		int		 _currentFrame{ -1 };
		int		 _frameCount{ -1 };
		int		 _currentClipIndex{ -1 };

	private:
		bool	 _isLoop{ false };
		bool	 _isInLayer{ false };
		bool	 _isFrameEnd{ false };
	};
}