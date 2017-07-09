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

	bgfx::VertexDecl vertexDeclaration()
	{
		bgfx::VertexDecl ret;
		ret
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.end();
		return ret;
	};

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

	bool compare(const Pos2fColorTextureVertex &other, bool otherwise) const {
		if (m_x < other.m_x) return true;
		if (m_x > other.m_x) return false;
		if (m_y < other.m_y) return true;
		if (m_y > other.m_y) return false;
		if (m_z < other.m_z) return true;
		if (m_z > other.m_z) return false;
		return otherwise;
	}

	bool operator<(const Pos2fColorTextureVertex &other) const {
		return compare(other, false);
	}

	bool operator>(const Pos2fColorTextureVertex &other) const {
		return !compare(other, true);
	}

	bgfx::VertexDecl vertexDeclaration()
	{
		bgfx::VertexDecl ret;
		ret
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();
		return ret;
	};
};