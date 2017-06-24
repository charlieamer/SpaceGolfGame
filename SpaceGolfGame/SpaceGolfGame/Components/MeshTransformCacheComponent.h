#pragma once

#include <vmath.h>

struct MeshTransformCacheComponent {
	MeshTransformCacheComponent() : transform(), valid(false) {}
	Matrix4f transform;
	bool valid;
};