#pragma once

#include <bgfx/bgfx.h>
#include <vmath.h>

template<typename T> bgfx::VertexDecl vertexDeclaration();

struct Pos2fColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	Pos2fColorVertex(Vector2f position) : m_x(position.x), m_y(position.y), m_z(0), m_abgr(0xffffffff) {}
	Pos2fColorVertex(Vector2f position, uint32_t color) : m_x(position.x), m_y(position.y), m_z(0), m_abgr(color) {}
};


struct Pos2fColorTextureVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;
	float m_tex_x;
	float m_tex_y;

	Pos2fColorTextureVertex(Vector2f position, Vector2f uv) : m_x(position.x), m_y(position.y), m_z(0), m_abgr(0xffffffff), m_tex_x(uv.x), m_tex_y(uv.y) {}
	Pos2fColorTextureVertex(Vector2f position, Vector2f uv, uint32_t color) : m_x(position.x), m_y(position.y), m_z(0), m_abgr(color), m_tex_x(uv.x), m_tex_y(uv.y) {}
};
