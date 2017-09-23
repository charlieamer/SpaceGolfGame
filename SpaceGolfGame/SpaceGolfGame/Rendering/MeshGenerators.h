#pragma once

#include "../Components/MeshComponent.h"
#include <bx/math.h>

template<typename VertexType>
void generateCircleVertices(uint32_t color, int vertices, std::vector<VertexType> &verticesResult, std::vector<uint16_t> &indicesResult)
{
	double angle = 0;

	for (int i = 0; i < vertices / 2; i++) {
		verticesResult.push_back(VertexType({ (float)cos(angle), (float)sin(angle) }, color));
		verticesResult.push_back(VertexType({ (float)cos(angle),-(float)sin(angle) }, color));
		angle += bx::kPi2 / (float)vertices;
	}
	verticesResult.push_back(VertexType({ -1.0f, 0.0f }, color));

	for (unsigned i = 0; i < verticesResult.size(); i++) {
		indicesResult.push_back(i);
	}
}

MeshComponent generateSolidCircleMesh(uint32_t color, int vertices = 10);
MeshComponent generatePoint(uint32_t color);
MeshComponent generatePoint(uint32_t color, uint64_t renderState);
MeshComponent generateTexturedRectangle(Aabb3f bounds, std::string texturePath, uint32_t tint);