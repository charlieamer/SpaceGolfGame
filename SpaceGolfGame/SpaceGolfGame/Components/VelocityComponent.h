#pragma once

#include <vmath.h>

struct VelocityComponent {
	VelocityComponent(Vector2f v) : v(v) {}
	VelocityComponent(float x, float y) : v(x, y) {}
	Vector2f v;
};