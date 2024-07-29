#include <BoxComponent.h>
#include <CollisionComponent.h>
#include <CoreManager.h>
#include <GraphicsManager.h>
#include <ACollision.h>
#include <Actor.h>

bool Engine::BoxComponent::InitializeComponent()
{
	_pCollision = ACollision::Create();
	if (!_pCollision)
	{
		return false;
	}

	_collider = Collider::COLLIDER_AABB;
	_type = Collision::COLLISION_BLOCK;

	return true;
}

void Engine::BoxComponent::TickComponent(_float deltaSeconds)
{
	SceneComponent::TickComponent(deltaSeconds);
	Mathf::Vector2 worldLocation = GetWorldLocation();
	_pCollision->SetCollisionOffset(worldLocation);
}

bool Engine::BoxComponent::IsCollision(CollisionComponent* pOther)
{
	if (pOther->GetColliderType() == Collider::COLLIDER_AABB)
	{
		BoxComponent* pBox = dynamic_cast<BoxComponent*>(pOther);
		if (pBox)
		{
			return _pCollision->CheckCollision(pBox->_pCollision);
		}
	}

	return false;
}

void Engine::BoxComponent::Render(_RenderTarget pRenderTarget)
{
	if (_type == Collision::COLLISION_IGNORE)
	{
		return;
	}

	Mathf::Matx3F Transform = _cameraMatrix;
	pRenderTarget->SetTransform(Transform);

	Mathf::Vector2 point = {
		_pCollision->GetCollisionOffset().x,
		_pCollision->GetCollisionOffset().y
	};

	ID2D1SolidColorBrush* m_pBrush = Graphics->GetBrush("Red");
	
	pRenderTarget->DrawLine(D2D1::Point2F(point.x - 5.0f, point.y), D2D1::Point2F(point.x + 5.0f, point.y), m_pBrush, 3.0f);
	pRenderTarget->DrawLine(D2D1::Point2F(point.x, point.y - 5.0f), D2D1::Point2F(point.x, point.y + 5.0f), m_pBrush, 3.0f);

	Mathf::RectF rect = {
		point.x - _pCollision->GetCollisionSize().x * 0.5f,
		point.y - _pCollision->GetCollisionSize().y * 0.5f,
		point.x + _pCollision->GetCollisionSize().x * 0.5f,
		point.y + _pCollision->GetCollisionSize().y * 0.5f
	};

	pRenderTarget->DrawRectangle(D2D1::RectF(rect.left, rect.top, rect.right, rect.bottom), m_pBrush, 3.0f);
}

void Engine::BoxComponent::SetAddOffset(const Mathf::Vector2& offsetVector)
{
	SetRelativeLocation(offsetVector);
}

void Engine::BoxComponent::SetSize(const Mathf::Vector2& sizeVector)
{
	_pCollision->SetCollisionSize(sizeVector);
}

void Engine::BoxComponent::Remove()
{
	Management->RemoveCollisionQueue(_owner->GetLayerIndex(),this);
	SafeRelease(_pCollision);
}

Engine::BoxComponent* Engine::BoxComponent::Create()
{
	BoxComponent* pInstance = new BoxComponent;
	if (pInstance->InitializeComponent())
	{
		return pInstance;
	}

	return nullptr;
}
