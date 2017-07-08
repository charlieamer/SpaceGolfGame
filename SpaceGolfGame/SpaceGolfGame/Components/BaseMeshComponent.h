#pragma once

#include "../Rendering/RenderingData.h"
#include <vector>

template<typename T>
struct BaseMeshComponent {
	std::vector<T> vertices;
	std::vector<uint16_t> indices;
	uint64_t renderState;
	bool visible;
};