#pragma once

#include <vmath.h>

struct VelocityComponent {
	VelocityComponent(Vector2f v) : v(v) {}
	Vector2f v;
};