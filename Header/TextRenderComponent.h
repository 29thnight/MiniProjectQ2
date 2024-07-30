#pragma once
#include <RenderComponent.h>
#include <Mathf.h>

namespace Engine
{
	class TextRenderComponent final : public RenderComponent
	{
	protected:
		explicit TextRenderComponent() = default;
		virtual ~TextRenderComponent() = default;

	public:
		virtual void TickComponent(_float deltaSeconds) override;
		virtual void Render(_RenderTarget pRenderTarget) override;

	public:
		void SetText(const string& text);
		void SetFont(_pwstring fontName);
		void SetSize(const Mathf::Vector2& size);
		void ChooseBrush(_pstring brushName);
		void SetColor(const Color& color);
		_pFontFormat GetFont() const { return _font; }

	public:
		virtual void SerializeIn(nlohmann::ordered_json& object) {};
		virtual void SerializeOut(nlohmann::ordered_json& object) {};

	public:
		static TextRenderComponent* Create();

	private:
		virtual bool InitializeComponent() override;
		virtual void Destroy() override;

	private:
		Brush		 _pBrush{ nullptr };
		Mathf::RectF _textRect{};
		Color		 _color{ D2D1::ColorF::White };

	private:
		_pFontFormat _font{ nullptr };
		string		 _text{};
	};
}