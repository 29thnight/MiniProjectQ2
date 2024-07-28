#pragma once
#include <RenderComponent.h>
#include <Mathf.h>

namespace Engine
{
	CORECLASS()
	class BitmapComponent : public RenderComponent
	{
	protected:
		using BitmapTextures = std::vector<Texture*>;

	protected:
		explicit BitmapComponent() = default;
		virtual ~BitmapComponent() = default;

	public:
		virtual void Render(_RenderTarget pRenderTarget) override;

	public:
		void SetTextures(BitmapTextures* vecTextures);
		void SetTextureIndex(int index) { _currentTextureIndex = index; }
		void SetTextureRect(Texture* pTexture);
		Mathf::RectF GetTextureRect();
	public:
		void SetTextureClipping(bool isTextureClipping) { _isTextureClipping = isTextureClipping; }
		bool IsTextureClipping() const { return _isTextureClipping; }
		void SetTextureClippingRect(const Mathf::RectF& textureClippingRect) { _textureClippingRect = textureClippingRect; }

	public:
		void SetBitmapLocalTransform();
		void SetBitmapIndex(int index) { _currentBitmapIndex = index; }
		void SetCenterAlignment(bool isCenterAlignment) { _isCenterAlignment = isCenterAlignment; }
		bool IsCenterAlignment() const { return _isCenterAlignment; }

	public:
		void SetFlip(bool isFlip) { _isFlip = isFlip; }
		bool IsFlip() const { return _isFlip; }

	protected:
		virtual bool InitializeComponent() override;
		virtual void Destroy() override;

	public:
		static BitmapComponent* Create();

	protected:
		BitmapTextures*		_vecTextures{ nullptr };
		Mathf::RectF		_textureRect{};
		Mathf::RectF		_textureClippingRect{};
		Mathf::Matx3F		_localTransform{ Matx::Identity };
		Mathf::Vector2		_localScale{ UnitVector::Zero };
		Mathf::Vector2		_localLocation{ UnitVector::Zero };
		int					_currentTextureIndex{ 0 };
		int					_currentBitmapIndex{ 0 };
		bool 				_isFlip{ false };
		bool				_isCenterAlignment{ true };
		bool				_isTextureClipping{ false };
	};
}