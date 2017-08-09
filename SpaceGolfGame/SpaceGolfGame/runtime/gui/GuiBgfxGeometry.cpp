#include "GuiBgfxGeometry.h"
#include <bx/fpumath.h>
#include "GuiBgfxRenderer.h"
using namespace CEGUI;

GuiBgfxGeometry::GuiBgfxGeometry(GuiBgfxRenderer & renderer) : owner(renderer)
{
	effect = NULL;
	texture = NULL;
	decl.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
		.end();
}


GuiBgfxGeometry::~GuiBgfxGeometry()
{
}

void GuiBgfxGeometry::registerBuffers(Batch &batch)
{
	destroyBuffers(batch);
	batch.indexHandle = bgfx::createIndexBuffer(bgfx::makeRef(batch.indices.data(), sizeof(batch.indices[0]) * batch.indices.size()));
	batch.vertexHandle = bgfx::createVertexBuffer(bgfx::makeRef(batch.vertices.data(), sizeof(batch.vertices[0]) * batch.vertices.size()), decl);
}

void GuiBgfxGeometry::destroyBuffers()
{
	for (auto& batch : batches) {
		destroyBuffers(batch);
	}
}

void GuiBgfxGeometry::destroyBuffers(Batch & batch)
{
	if (batch.vertexHandle.idx != bgfx::kInvalidHandle) {
		bgfx::destroyIndexBuffer(batch.indexHandle);
		bgfx::destroyVertexBuffer(batch.vertexHandle);
		batch.vertexHandle = BGFX_INVALID_HANDLE;
		batch.indexHandle = BGFX_INVALID_HANDLE;
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
	uint32_t transformCache = bgfx::setTransform(matrix);
	for (auto& batch : batches) {
		if (batch.indexHandle.idx == bgfx::kInvalidHandle) {
			continue;
		}
		bgfx::setTransform(transformCache);
		bgfx::setIndexBuffer(batch.indexHandle);
		bgfx::setVertexBuffer(0, batch.vertexHandle);
		if (batch.clipping) {
			//bgfx::setScissor(currentClipping.d_min.d_x, currentClipping.d_min.d_y, currentClipping.d_max.d_x, currentClipping.d_max.d_y);
		}
		else {
			//bgfx::setScissor(0, 0, -1, -1);
		}
		if (batch.texture && batch.texture->getHandle().idx != bgfx::kInvalidHandle) {
			bgfx::setTexture(0, uniform, batch.texture->getHandle());
		}
		else {
			bgfx::setTexture(0, uniform, BGFX_INVALID_HANDLE);
		}
		bgfx::setState(BGFX_STATE_RGB_WRITE | BGFX_STATE_ALPHA_WRITE | BGFX_STATE_PT_LINES | BGFX_STATE_BLEND_ALPHA);
		bgfx::submit(owner.getCurrentPass(), program);
	}
	//bgfx::setScissor(0, 0, -1, -1);
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
	currentClipping = region;
}

void GuiBgfxGeometry::appendVertex(const Vertex & vertex)
{
	appendGeometry(&vertex, 1);
}

void GuiBgfxGeometry::appendGeometry(const Vertex * const vbuff, uint vertex_count)
{
	addBatchIfNecessary();
	Batch& current = currentBatch();
	for (unsigned i = 0; i < vertex_count; i++) {
		current.indices.push_back(current.vertices.size());
		current.vertices.emplace_back(vbuff[i]);
	}
	registerBuffers(current);
}

Batch & GuiBgfxGeometry::currentBatch()
{
	return batches[batches.size() - 1];
}

void GuiBgfxGeometry::addBatchIfNecessary()
{
	if (batches.size() == 0 || currentBatch().vertices.size() > 0) {
		batches.emplace_back();
	}
	Batch& batch = currentBatch();
	batch.clipping = clipping;
	batch.texture = texture;
}

void GuiBgfxGeometry::setActiveTexture(Texture * texture)
{
	this->texture = static_cast<GuiBgfxTexture*>(texture);
}

void GuiBgfxGeometry::reset()
{
	destroyBuffers();
	batches.clear();
}

Texture * GuiBgfxGeometry::getActiveTexture() const
{
	return texture;
}

uint GuiBgfxGeometry::getVertexCount() const
{
	uint ret = 0;
	for (auto& batch : batches) {
		ret += batch.vertices.size();
	}
	return ret;
}

uint GuiBgfxGeometry::getBatchCount() const
{
	return batches.size();
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
	clipping = active;
}

bool GuiBgfxGeometry::isClippingActive() const
{
	return clipping;
}

void GuiBgfxGeometry::setProgramHandle(bgfx::ProgramHandle programHandle, bgfx::UniformHandle uniformHandle)
{
	program = programHandle;
	uniform = uniformHandle;
}
