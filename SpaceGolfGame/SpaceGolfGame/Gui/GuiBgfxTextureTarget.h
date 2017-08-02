#pragma once
#include <CEGUI/CEGUI.h>
using namespace CEGUI;
#include "GuiBgfxRenderTarget.h"
#include <bgfx/bgfx.h>

class GuiBgfxTextureTarget : public TextureTarget, public GuiBgfxRenderTarget
{
	bgfx::FrameBufferHandle handle;
	const bgfx::Memory* textureMemory;
	virtual void updateArea() override;
public:
	GuiBgfxTextureTarget(GuiBgfxRenderer& owner);
	~GuiBgfxTextureTarget();

	// Inherited via TextureTarget
	virtual bool isImageryCache() const override;
	virtual void activate() override;
	virtual void deactivate() override;
	virtual void clear() override;
	virtual Texture & getTexture() const override;
	virtual void declareRenderSize(const Sizef & sz) override;
	virtual bool isRenderingInverted() const override;

	GuiBgfxTexture* texture;
	virtual void destroy() override;
};

