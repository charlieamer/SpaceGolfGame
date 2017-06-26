#pragma once

#include "../Rendering/RenderingData.h"
#include <vector>

struct BaseMeshComponent {
	std::vector<Pos2fColorVertex> vertices;
	std::vector<uint16_t> indices;
	uint64_t renderState;
	bool visible;
};