#pragma once
#include <CEGUI/CEGUI.h>
#include <vector>
#include "GuiBgfxTexture.h"
#include <bgfx/bgfx.h>

using namespace std;

class GuiBgfxRenderer;

struct GuiBgfxVertex {
	GuiBgfxVertex(CEGUI::Vertex vert) {
		x = vert.position.d_x;
		y = vert.position.d_y;
		z = vert.position.d_z;
		u = vert.tex_coords.d_x;
		v = vert.tex_coords.d_y;
		a = vert.colour_val.getAlpha();
		b = vert.colour_val.getBlue();
		g = vert.colour_val.getGreen();
		r = vert.colour_val.getRed();
	}

	float x, y, z;
	float u, v;
	unsigned char a, b, g, r;
};

class GuiBgfxGeometry : public CEGUI::GeometryBuffer
{
	vector<GuiBgfxVertex> vertices;
	vector<uint16_t> indices;
	bgfx::VertexBufferHandle vertexHandle;
	bgfx::IndexBufferHandle indexHandle;
	bgfx::ProgramHandle program;
	bgfx::UniformHandle uniform;

	GuiBgfxTexture* texture;

	CEGUI::RenderEffect *effect;
	CEGUI::Vector3f translation;
	CEGUI::Quaternion rotation;
	CEGUI::Vector3f pivot;
	CEGUI::Rectf clipping;
	bool isClipping;

	void registerBuffers();
	bgfx::VertexDecl decl;

	void updateMatrix();
	float matrix[16];

	GuiBgfxRenderer& owner;
public:
	GuiBgfxGeometry(GuiBgfxRenderer & owner);
	~GuiBgfxGeometry();

	// Inherited via GeometryBuffer
	virtual void draw() const override;
	virtual void setTranslation(const CEGUI::Vector3f & v) override;
	virtual void setRotation(const CEGUI::Quaternion & r) override;
	virtual void setPivot(const CEGUI::Vector3f & p) override;
	virtual void setClippingRegion(const CEGUI::Rectf & region) override;
	virtual void appendVertex(const CEGUI::Vertex & vertex) override;
	virtual void appendGeometry(const CEGUI::Vertex * const vbuff, CEGUI::uint vertex_count) override;
	virtual void setActiveTexture(CEGUI::Texture * texture) override;
	virtual void reset() override;
	virtual CEGUI::Texture * getActiveTexture() const override;
	virtual CEGUI::uint getVertexCount() const override;
	virtual CEGUI::uint getBatchCount() const override;
	virtual void setRenderEffect(CEGUI::RenderEffect * effect) override;
	virtual CEGUI::RenderEffect * getRenderEffect() override;
	virtual void setClippingActive(const bool active) override;
	virtual bool isClippingActive() const override;

	void setProgramHandle(bgfx::ProgramHandle programHandle, bgfx::UniformHandle uniformHandle);
	void destroyBuffers();
};

