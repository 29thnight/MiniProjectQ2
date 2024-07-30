#include <Actor.h>
#include <CollisionComponent.h>
#include <CoreManager.h>
#include <GraphicsManager.h>
#include <ACollision.h>
#include <RCollision.h>
#include <BoxComponent.h>
#include <RayCastComponent.h>

bool Engine::RayCastComponent::InitializeComponent()
{
	_pCollision = RCollision::Create();
	if (!_pCollision)
	{
		return false;
	}

	_collider = Collider::COLLIDER_RAYCAST;
	_type = Collision::COLLISION_BLOCK;

	return true;
}

void Engine::RayCastComponent::TickComponent(_float deltaSeconds)
{
	SceneComponent::TickComponent(deltaSeconds);
	Mathf::Vector2 worldLocation = GetWorldLocation();
	_pCollision->SetOrigin(worldLocation);
}

bool Engine::RayCastComponent::IsCollision(CollisionComponent* pOther)
{
	switch (pOther->GetColliderType())
	{
	case Collider::COLLIDER_AABB:
	{
		BoxComponent* pBox = dynamic_cast<BoxComponent*>(pOther);
		if (pBox)
		{
			return _pCollision->CheckCollision(pBox->GetCollision());
		}
	}
	break;
	default:
	break;
	}

	return false;
}

void Engine::RayCastComponent::Render(_RenderTarget pRenderTarget)
{
	if (_type == Collision::COLLISION_IGNORE)
	{
		return;
	}

	Mathf::Matx3F Transform = _cameraMatrix;
	pRenderTarget->SetTransform(Transform);

	Mathf::Vector2 point = {
		_pCollision->GetOrigin().x,
		_pCollision->GetOrigin().y
	};

	ID2D1SolidColorBrush* m_pBrush = Graphics->GetBrush("Red");

	pRenderTarget->DrawLine(D2D1::Point2F(point.x - 5.0f, point.y), D2D1::Point2F(point.x + 5.0f, point.y), m_pBrush, 3.0f);

	Mathf::Vector2 direction = {
		_pCollision->GetRayDirection().x,
		_pCollision->GetRayDirection().y
	};

	pRenderTarget->DrawLine(D2D1::Point2F(point.x, point.y), D2D1::Point2F(point.x + direction.x, point.y + direction.y), m_pBrush, 3.0f);
}

void Engine::RayCastComponent::SetAddOffset(const Mathf::Vector2& offsetVector)
{
	SetRelativeLocation(offsetVector);
}

void Engine::RayCastComponent::SetSize(const Mathf::Vector2& sizeVector)
{
	_pCollision->SetRayDirection(sizeVector);
}

void Engine::RayCastComponent::Destroy()
{
	Management->RemoveCollisionQueue(_owner->GetLayerIndex(), this);
	SafeDelete(_pCollision);
}

Engine::RayCastComponent* Engine::RayCastComponent::Create()
{
	return new RayCastComponent();
}