#include "GuiBgfxRenderTarget.h"
#include <bgfx/bgfx.h>
#include <bx/fpumath.h>

void GuiBgfxRenderTarget::updateArea()
{
	area = Rectf(0, 0, bgfx::getStats()->width, bgfx::getStats()->height);
}

GuiBgfxRenderTarget::GuiBgfxRenderTarget(GuiBgfxRenderer& owner) : owner(owner)
{
}


GuiBgfxRenderTarget::~GuiBgfxRenderTarget()
{
}

void GuiBgfxRenderTarget::draw(const GeometryBuffer & buffer)
{
	buffer.draw();
}

void GuiBgfxRenderTarget::draw(const RenderQueue & queue)
{
	queue.draw();
}

void GuiBgfxRenderTarget::setArea(const Rectf & area)
{
	CEGUI_THROW(new RendererException("Set area supported in render target"));
}

const Rectf & GuiBgfxRenderTarget::getArea() const
{
	return area;
}

bool GuiBgfxRenderTarget::isImageryCache() const
{
	return false;
}

void GuiBgfxRenderTarget::activate()
{
	owner.activateTarget(this);
	updateArea();
	Rectf area = this->getArea();

	int width = area.getWidth();
	int height = area.getHeight();
	float ortho[16];
	bx::mtxOrtho(ortho, 0, -width, height, 0, 0, 100, 0, false);
	float at[3] = { 0, 0, 0.0f };
	float eye[3] = { 0, 0, 1.0f };
	float up[3] = { 0.0f, 1.0f, 0.0f };
	float transform[16];
	bx::mtxLookAt(transform, eye, at, up);
	bgfx::setViewTransform(getPassId(), transform, ortho);
	bgfx::setViewRect(getPassId(), 0, 0, width, height);
	bgfx::setViewClear(getPassId(), 0);
}

void GuiBgfxRenderTarget::deactivate()
{
}

void GuiBgfxRenderTarget::unprojectPoint(const GeometryBuffer & buff, const Vector2f & p_in, Vector2f & p_out) const
{
	CEGUI_THROW(new RendererException("Unproject point not supported"));
}
