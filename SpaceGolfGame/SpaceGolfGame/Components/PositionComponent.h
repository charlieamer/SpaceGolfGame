#pragma once
#include <vmath.h>

struct PositionComponent
{
	Vector2f pos;
	PositionComponent(Vector2f vec) : pos(vec) {}
	PositionComponent(float xx, float yy) : pos(xx, yy) {}
	PositionComponent() : pos(0, 0) {}
};
