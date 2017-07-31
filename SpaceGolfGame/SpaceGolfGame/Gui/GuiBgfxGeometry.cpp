#include "GuiBgfxGeometry.h"
#include <bx/fpumath.h>
#include "GuiBgfxRenderer.h"
using namespace CEGUI;

GuiBgfxGeometry::GuiBgfxGeometry(GuiBgfxRenderer & renderer) : owner(renderer)
{
	effect = NULL;
	indexHandle = BGFX_INVALID_HANDLE;
	vertexHandle = BGFX_INVALID_HANDLE;
	decl.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8)
		.end();
}


GuiBgfxGeometry::~GuiBgfxGeometry()
{
}

void GuiBgfxGeometry::registerBuffers()
{
	destroyBuffers();
	bgfx::createIndexBuffer(bgfx::makeRef(indices.data(), sizeof(indices[0]) * indices.size()));
	bgfx::createVertexBuffer(bgfx::makeRef(vertices.data(), sizeof(vertices[0]) * vertices.size()), decl);
}

void GuiBgfxGeometry::destroyBuffers()
{
	if (vertexHandle.idx != bgfx::kInvalidHandle) {
		bgfx::destroyIndexBuffer(indexHandle);
		bgfx::destroyVertexBuffer(vertexHandle);
	}
}

void GuiBgfxGeometry::updateMatrix()
{
	bx::mtxIdentity(matrix);
	Vector3f pivoted = pivot + translation;
	bx::mtxTranslate(matrix, pivoted.d_x, pivoted.d_y, pivoted.d_z);

	float quat[4] = { rotation.d_x , rotation.d_y, rotation.d_z, rotation.d_w }, tmp1[16], tmp2[16];
	bx::mtxQuat(tmp1, quat);
	bx::mtxMul(tmp2, matrix, tmp1);
	memcpy_s(matrix, sizeof(float) * 16, tmp2, sizeof(float) * 16);
	
	bx::mtxIdentity(tmp1);
	bx::mtxTranslate(tmp1, -pivot.d_x, -pivot.d_y, -pivot.d_z);
	bx::mtxMul(tmp2, matrix, tmp1);
	memcpy_s(matrix, sizeof(float) * 16, tmp2, sizeof(float) * 16);
}

void GuiBgfxGeometry::draw() const
{
	bgfx::setTransform(matrix);
	bgfx::setIndexBuffer(indexHandle);
	bgfx::setVertexBuffer(0, vertexHandle);
	if (isClipping) {
		bgfx::setScissor(clipping.d_min.d_x, clipping.d_min.d_y, clipping.d_max.d_x, clipping.d_max.d_y);
	}
	else {
		bgfx::setScissor(0, 0, -1, -1);
	}
	if (texture && texture->getHandle().idx != bgfx::kInvalidHandle) {
		bgfx::setTexture(0, uniform, texture->getHandle());
	}
	else {
		bgfx::setTexture(0, uniform, BGFX_INVALID_HANDLE);
	}
	bgfx::submit(owner.getCurrentPass(), program);
	bgfx::setScissor(0, 0, -1, -1);
}

void GuiBgfxGeometry::setTranslation(const Vector3f & v)
{
	translation = v;
	updateMatrix();
}

void GuiBgfxGeometry::setRotation(const Quaternion & r)
{
	rotation = r;
	updateMatrix();
}

void GuiBgfxGeometry::setPivot(const Vector3f & p)
{
	pivot = p;
	updateMatrix();
}

void GuiBgfxGeometry::setClippingRegion(const Rectf & region)
{
	clipping = region;
}

void GuiBgfxGeometry::appendVertex(const Vertex & vertex)
{
	indices.push_back(vertices.size());
	vertices.emplace_back(vertex);
	registerBuffers();
}

void GuiBgfxGeometry::appendGeometry(const Vertex * const vbuff, uint vertex_count)
{
	for (int i = 0; i < vertex_count; i++) {
		appendVertex(vbuff[i]);
	}
}

void GuiBgfxGeometry::setActiveTexture(Texture * texture)
{
	this->texture = static_cast<GuiBgfxTexture*>(texture);
}

void GuiBgfxGeometry::reset()
{
	destroyBuffers();
	vertices.clear();
	indices.clear();
}

Texture * GuiBgfxGeometry::getActiveTexture() const
{
	return texture;
}

uint GuiBgfxGeometry::getVertexCount() const
{
	return vertices.size();
}

uint GuiBgfxGeometry::getBatchCount() const
{
	return 1;
}

void GuiBgfxGeometry::setRenderEffect(RenderEffect * effect)
{
	this->effect = effect;
}

RenderEffect * GuiBgfxGeometry::getRenderEffect()
{
	return effect;
}

void GuiBgfxGeometry::setClippingActive(const bool active)
{
	isClipping = active;
}

bool GuiBgfxGeometry::isClippingActive() const
{
	return isClipping;
}

void GuiBgfxGeometry::setProgramHandle(bgfx::ProgramHandle programHandle, bgfx::UniformHandle uniformHandle)
{
	program = programHandle;
	uniform = uniformHandle;
}
