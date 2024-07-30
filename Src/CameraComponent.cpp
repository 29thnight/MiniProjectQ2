#include <CameraComponent.h>
#include <CoreManager.h>
#include <ACollision.h>

void Engine::CameraComponent::TickComponent(_float deltaSeconds)
{
	SceneComponent::TickComponent(deltaSeconds);

	float Width = (float)Management->setting.width;
	float Height = (float)Management->setting.height;

	float halfWidth = Width * 0.5f;
	float halfHeight = Height * 0.5f;

	Mathf::Vector2 CollisionPosition = Mathf::Vector2{ _RelativeLocation.x, _RelativeLocation.y };

	_pCollision->SetCollisionSize({ Width, Height });
	_pCollision->SetCollisionOffset(CollisionPosition);
}

bool Engine::CameraComponent::CheckCollision(ACollision* pCollision)
{
	return _pCollision->CheckCollision(pCollision);
}

bool Engine::CameraComponent::InitializeComponent()
{
	_pCollision = ACollision::Create();

	return true;
}

void Engine::CameraComponent::Destroy()
{
	SafeDelete(_pCollision);
}

Engine::CameraComponent* Engine::CameraComponent::Create()
{
	return new CameraComponent();
}
