#include <ACollision.h>
#include <Mathf.h>

void Engine::ACollision::SetCollisionScale(const Mathf::Vector2& collisionScale)
{
	_collisionSize.x *= collisionScale.x;
	_collisionSize.y *= collisionScale.y;

	_collisionOffset.x *= collisionScale.x;
	_collisionOffset.y *= collisionScale.y;
}

bool Engine::ACollision::CheckCollision(ACollision* pCollision) const
{
	float thisLeft = _collisionOffset.x - _collisionSize.x * 0.5f;
	float thisRight = _collisionOffset.x + _collisionSize.x * 0.5f;
	float thisTop = _collisionOffset.y - _collisionSize.y * 0.5f;
	float thisBottom = _collisionOffset.y + _collisionSize.y * 0.5f;

	float otherLeft = pCollision->GetCollisionOffset().x - pCollision->GetCollisionSize().x * 0.5f;
	float otherRight = pCollision->GetCollisionOffset().x + pCollision->GetCollisionSize().x * 0.5f;
	float otherTop = pCollision->GetCollisionOffset().y - pCollision->GetCollisionSize().y * 0.5f;
	float otherBottom = pCollision->GetCollisionOffset().y + pCollision->GetCollisionSize().y * 0.5f;

	if (thisRight < otherLeft || thisLeft > otherRight || thisBottom < otherTop || thisTop > otherBottom)
	{
		return false;
	}

	return true;
}
