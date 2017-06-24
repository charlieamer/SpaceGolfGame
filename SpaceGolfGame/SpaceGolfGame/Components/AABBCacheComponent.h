#pragma once

#include <vmath.h>

struct AABBCacheComponent {
	AABBCacheComponent() : AABB(), valid(false) {}
	Aabb3f AABB;
	bool valid;
};