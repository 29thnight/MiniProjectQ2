#include <CameraActor.h>
#include <CameraComponent.h>
#include <CoreManager.h>
#include <World.h>
#include <Actor.h>
#include <ObjectPtr.h>
#include <CoreBase.h>
#include <ActorComponent.h>

void Engine::CameraActor::Tick(_float deltaSeconds)
{
	if (!_isTracking)
		return;

	if (!_pOwnerWorld)
		return;

	Actor::Tick(deltaSeconds);

	Mathf::RectF worldSize = _pOwnerWorld->GetWorldSize();
	float halfWidth = Management->setting.width / 2.f;
	float halfHeight = Management->setting.height / 2.f;

	Mathf::Vector2 parentLocation = _pParent->GetRootComponent()->GetRelativeLocation();
	//Mathf::Vector2 cameraCenter = _cameraComponent->GetCenterPosition();
	Mathf::Vector2 cameraCenter = Mathf::Vector2{ halfWidth, halfHeight };
	Mathf::Vector2 cameraOffset = _cameraComponent->GetCameraOffset();
	Mathf::Vector2 cameraLocation = _cameraComponent->GetRelativeLocation();

	Mathf::Vector2 targetLocation = ( parentLocation - cameraCenter - cameraOffset );
	Mathf::Vector2 newLocation = Mathf::Lerp(cameraLocation, targetLocation, _cameraLerpFactor * deltaSeconds);

	if (targetLocation != _oldLocation)
	{
		_isMove = true;
	}
	else
	{
		_isMove = false;
	}

	if (targetLocation.x > _oldLocation.x)
	{
		_moveDirectionFlag = MoveDirectionFlag::Right;
	}
	else if (targetLocation.x < _oldLocation.x)
	{
		_moveDirectionFlag = MoveDirectionFlag::Left;
	}
	else if (targetLocation.y > _oldLocation.y)
	{
		_moveDirectionFlag = MoveDirectionFlag::Down;
	}
	else if (targetLocation.y < _oldLocation.y)
	{
		_moveDirectionFlag = MoveDirectionFlag::Up;
	}
	else
	{
		_moveDirectionFlag = 0;
	}

	if(0 != worldSize.bottom && 0 != worldSize.right)
	{
		if (newLocation.x - halfWidth < worldSize.left)
		{
			newLocation.x = worldSize.left + halfWidth;
			_isMove = false;
		}

		if (newLocation.x + halfWidth > worldSize.right)
		{
			newLocation.x = worldSize.right - halfWidth;
			_isMove = false;
		}

		if (newLocation.y - halfHeight < worldSize.top)
		{
			newLocation.y = worldSize.top + halfHeight;
			_isMove = false;
		}

		if (newLocation.y + halfHeight > worldSize.bottom)
		{
			newLocation.y = worldSize.bottom - halfHeight;
			_isMove = false;
		}
	}

	_cameraComponent->SetRelativeLocation(newLocation);
	_oldLocation = targetLocation;
}

void Engine::CameraActor::TrackTarget(Actor* pTarget)
{
	_pParent = pTarget;
}

bool Engine::CameraActor::Initialize()
{
	_cameraComponent = CameraComponent::Create();
	_cameraComponent->SetOwner(this);
	_cameraComponent->InitializeComponent();

	SetRootComponent(_cameraComponent);
	_vecComponents.push_back(MakeObjectPtr<ActorComponent>(_cameraComponent));

	BeginPlay();

    return true;
}

void Engine::CameraActor::Destroy()
{
	Actor::Destroy();
}

Engine::CameraActor* Engine::CameraActor::Create()
{
	CameraActor* pInstance = new CameraActor;
	if (pInstance->Initialize())
		return pInstance;

	return nullptr;
}
