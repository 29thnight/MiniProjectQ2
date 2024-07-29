#include <BitmapComponent.h>
#include <Mathf.h>
#include <Texture.h>
#include <ACollision.h>

void Engine::BitmapComponent::Render(_RenderTarget pRenderTarget)
{
	if (!_vecTextures) { return; }
	if (_vecTextures->empty()) { return; }
	if (!_isVisible) { return; }

	Texture* pTexture = _vecTextures->at(_currentTextureIndex);

	SetTextureRect(pTexture);

	SetBitmapLocalTransform();

	Mathf::Matx3F flipMatrix = Matx::Identity;
	switch (_isCenterAlignment)
	{
	case true:
		if (_isFlip)
		{
			flipMatrix = Mathf::Scale({-1.f, 1.f}, 
				Mathf::Point2F{_textureRect.right * 0.5f, _textureRect.bottom * 0.5f}) * _localTransform;
		}
		else
		{
			flipMatrix = _localTransform;
		}
		break;
	case false:
		if (_isFlip)
		{
			flipMatrix = Mathf::Scale(Mathf::Vector2{-1.f, 1.f}, 
				Mathf::Point2F{_textureRect.right * 0.5f, _textureRect.bottom * 0.5f});
		}
		else
		{
			flipMatrix = Matx::Identity;
		}
		break;
	}

	
	Mathf::Matx3F Transform = flipMatrix * _WorldTransform * _cameraMatrix;

	pRenderTarget->SetTransform(Transform);

	switch (_isTextureClipping)
	{
	case true:

		pRenderTarget->PushAxisAlignedClip(_textureClippingRect, D2D1_ANTIALIAS_MODE_ALIASED);
		pRenderTarget->DrawBitmap((*pTexture)[_currentBitmapIndex]);
		pRenderTarget->PopAxisAlignedClip();

		break;
	case false:

		pRenderTarget->DrawBitmap((*pTexture)[_currentBitmapIndex]);

		break;
	}

	pRenderTarget->SetTransform(Matx::Identity);
}

void Engine::BitmapComponent::SetTextures(BitmapTextures* vecTextures)
{
	_vecTextures = vecTextures;

	AddRenderQueueInLayer();
}

void Engine::BitmapComponent::SetTextureRect(Texture* pTexture)
{
	Mathf::SizeF _size = (*pTexture)[0]->GetSize();

	_textureRect = D2D1::RectF(0, 0, _size.width, _size.height);

	_pCollision->SetCollisionSize({ _textureRect.right * _RelativeScale.x, _textureRect.bottom * _RelativeScale.y });
}

Mathf::RectF Engine::BitmapComponent::GetTextureRect()
{
	if (!_vecTextures) { return Mathf::RectF(); }
	if (0 == _textureRect.right || 0 == _textureRect.bottom) 
	{ 
		Texture* pTexture = _vecTextures->at(_currentTextureIndex);
		SetTextureRect(pTexture); 
	}

	return _textureRect;
}

void Engine::BitmapComponent::SetBitmapLocalTransform()
{
	_localLocation.x = _textureRect.right * 0.5f;
	_localLocation.y = _textureRect.bottom * 0.5f;

	_localTransform = Mathf::Translation(Mathf::Vector2{-_localLocation.x, -_localLocation.y});
}

bool Engine::BitmapComponent::InitializeComponent()
{
	if (!_pCollision)
	{
		_pCollision = ACollision::Create();
	}

    return true;
}

void Engine::BitmapComponent::Destroy()
{
	SafeDelete(_pCollision);
}

Engine::BitmapComponent* Engine::BitmapComponent::Create()
{
	BitmapComponent* pInstance = new BitmapComponent;
	if (pInstance->InitializeComponent())
	{
		return pInstance;
	}

	return nullptr;
}
