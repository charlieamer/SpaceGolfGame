#pragma once
#include <CEGUI/CEGUI.h>
using namespace CEGUI;
#include "GuiBgfxRenderer.h"

class GuiBgfxRenderTarget : public RenderTarget
{
protected:
	GuiBgfxRenderer& owner;
	uint8_t passId;
	Rectf area;
	virtual void updateArea();
public:
	GuiBgfxRenderTarget(GuiBgfxRenderer& owner);
	~GuiBgfxRenderTarget();

	virtual void destroy() {}

	// Inherited via RenderTarget
	virtual void draw(const GeometryBuffer & buffer) override;
	virtual void draw(const RenderQueue & queue) override;
	virtual void setArea(const Rectf & area) override;
	virtual const Rectf & getArea() const override;
	virtual bool isImageryCache() const override;
	virtual void activate() override;
	virtual void deactivate() override;
	virtual void unprojectPoint(const GeometryBuffer & buff, const Vector2f & p_in, Vector2f & p_out) const override;

	void setPassId(uint8_t value) { passId = value; }
	uint8_t getPassId() { return passId; }
};

