#include "GuiBgfxTextureTarget.h"
#include <bgfx/bgfx.h>

GuiBgfxTextureTarget::GuiBgfxTextureTarget(GuiBgfxRenderer& owner) : GuiBgfxRenderTarget(owner)
{
	texture = NULL;
}

GuiBgfxTextureTarget::~GuiBgfxTextureTarget()
{
}

bool GuiBgfxTextureTarget::isImageryCache() const
{
	return true;
}

void GuiBgfxTextureTarget::activate()
{
	bgfx::setViewFrameBuffer(getPassId(), handle);
}

void GuiBgfxTextureTarget::deactivate()
{
}

void GuiBgfxTextureTarget::clear()
{
	memset(textureMemory->data, 0, textureMemory->size);
	bgfx::updateTexture2D(texture->getHandle(), 0, 0, 0, 0, texture->getSize().d_width, texture->getSize().d_height, textureMemory);
}
Texture & GuiBgfxTextureTarget::getTexture() const
{
	return *texture;
}

void GuiBgfxTextureTarget::declareRenderSize(const Sizef & sz)
{
	/*
	if (texture) {
		CEGUI_THROW(new RendererException("Texture for render target alredy initialized"));
	}
	texture = new GuiBgfxTexture("Texture render target");
	uint8_t* data = new uint8_t[sz.d_width * sz.d_height * 4];
	textureMemory = bgfx::makeRef(data, sz.d_height * sz.d_width * 4);
	texture->loadFromMemory(textureMemory, sz, CEGUI::Texture::PixelFormat::PF_RGBA);
	*/

	handle = bgfx::createFrameBuffer(sz.d_width, sz.d_height, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT_WRITE_ONLY);
	area = Rectf(0, 0, sz.d_width, sz.d_height);
}

bool GuiBgfxTextureTarget::isRenderingInverted() const
{
	return true;
}

void GuiBgfxTextureTarget::destroy()
{
	if (texture) {
		texture->destroy();
		delete textureMemory->data;
	}
	bgfx::destroy(handle);
}
