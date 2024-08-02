#pragma once
#include <CoreBase.h>
#include <CoreDefine.h>
#include <rlottie.h>
#include <Mathf.h>

namespace Engine
{
	class Animation : public CoreBase
	{
	protected:
		explicit Animation() = default;
		virtual ~Animation() = default;

	public:
		ID2D1Bitmap* operator[](_uint index) { return _textures[index].Get(); }

	public:
		bool LoadAnimation(_pwstring fileName);
		size_t size() const { return _textures.size(); }
		Mathf::SizeF GetCanvasSize() const;
		size_t GetTotalFrame() const { return _totalFrame; }
		std::shared_ptr<rlottie::Animation> GetRlottieAnimation() const { return _animation; }
		_float GetFrameRate() const { return _frameRate; }

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) {};
		virtual void SerializeOut(nlohmann::ordered_json& object) {};

	public:
		static Animation* Create();
		void Destroy() override;

	private:
		std::string							_path{};
		std::shared_ptr<rlottie::Animation>	_animation{};
		std::vector<SmartPtr<ID2D1Bitmap>>	_textures{};

	private:
		double _frameRate{ };
		size_t _width{ };
		size_t _height{ };
		size_t _totalFrame{ };
		bool   _isLoop{ false };
	};
};