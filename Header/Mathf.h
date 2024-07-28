#pragma once
#include <Vector2.h>
#include <Matx.h>

namespace Mathf
{
	typedef D2D1_RECT_F RectF;
	typedef D2D1_SIZE_F SizeF;
}

namespace Mathf
{
	const float Rad2Deg = 180.f / DirectX::XM_PI;
	const float Deg2Rad = DirectX::XM_PI / 180.f;
}