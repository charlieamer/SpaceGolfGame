#pragma once

#include <bgfx/bgfx.h>
#include <vmath.h>

struct Pos2fColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;

	Pos2fColorVertex(Vector2f position) : m_x(position.x), m_y(position.y), m_z(0), m_abgr(0xffffffff) {}
	Pos2fColorVertex(Vector2f position, uint32_t color) : m_x(position.x), m_y(position.y), m_z(0), m_abgr(color) {}

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
	};

	static bgfx::VertexDecl ms_decl;

	bool compare(const Pos2fColorVertex &other, bool otherwise) const {
		if (m_x < other.m_x) return true;
		if (m_x > other.m_x) return false;
		if (m_y < other.m_y) return true;
		if (m_y > other.m_y) return false;
		if (m_z < other.m_z) return true;
		if (m_z > other.m_z) return false;
		return otherwise;
	}

	bool operator<(const Pos2fColorVertex &other) const {
		return compare(other, false);
	}

	bool operator>(const Pos2fColorVertex &other) const {
		return !compare(other, true);
	}
};