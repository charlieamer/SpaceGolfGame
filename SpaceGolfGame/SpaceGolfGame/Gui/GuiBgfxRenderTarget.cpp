#include "GuiBgfxRenderTarget.h"
#include <bgfx/bgfx.h>
#include <bx/fpumath.h>

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
	// CEGUI_THROW(new RendererException("Set area supported in render target"));
	return Rectf(0, 0, bgfx::getStats()->width, bgfx::getStats()->height);
}

bool GuiBgfxRenderTarget::isImageryCache() const
{
	return false;
}

void GuiBgfxRenderTarget::activate()
{
}

void GuiBgfxRenderTarget::deactivate()
{
}

void GuiBgfxRenderTarget::unprojectPoint(const GeometryBuffer & buff, const Vector2f & p_in, Vector2f & p_out) const
{
	CEGUI_THROW(new RendererException("Unproject point not supported"));
}
