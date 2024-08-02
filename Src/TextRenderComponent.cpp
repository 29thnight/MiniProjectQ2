#include <GraphicsManager.h>
#include <FontManager.h>
#include <TextRenderComponent.h>

void Engine::TextRenderComponent::TickComponent(_duration deltaSeconds)
{
	SceneComponent::TickComponent(deltaSeconds);
}

void Engine::TextRenderComponent::Render(_RenderTarget pRenderTarget)
{
	if (!_font)
		return;

	Mathf::Matx3F Transform = _WorldTransform * _cameraMatrix;
	pRenderTarget->SetTransform(Transform);
	pRenderTarget->DrawTextW(_text, _text.length(), _font, _textRect, _pBrush);

#ifdef _DEBUG
	pRenderTarget->DrawRectangle({_textRect.left, _textRect.top, _textRect.right, _textRect.bottom}, _pBrush, 3.0f);
#endif // _DEBUG

}

void Engine::TextRenderComponent::SetText(const string& text)
{
	_text = text;
}

void Engine::TextRenderComponent::SetFont(_pwstring fontName)
{
	_font = FontMgr->GetFont(fontName);
}

void Engine::TextRenderComponent::SetSize(const Mathf::Vector2& size)
{
	Mathf::Vector2 rectHalfSize = size * 0.5f;
	Mathf::Vector2 position = GetWorldLocation();

	_textRect.left	 = -rectHalfSize.x;
	_textRect.top	 = -rectHalfSize.y;
	_textRect.right  =  rectHalfSize.x;
	_textRect.bottom =  rectHalfSize.y;
}

void Engine::TextRenderComponent::ChooseBrush(_pstring brushName)
{
	_pBrush = Graphics->GetBrush(brushName);
}

void Engine::TextRenderComponent::SetColor(const Color& color)
{
	if(!_pBrush)
		return;

	_pBrush->SetColor(color);
}

Engine::TextRenderComponent* Engine::TextRenderComponent::Create()
{
	return new TextRenderComponent();
}

bool Engine::TextRenderComponent::InitializeComponent()
{
	return true;
}

void Engine::TextRenderComponent::Destroy()
{
}
