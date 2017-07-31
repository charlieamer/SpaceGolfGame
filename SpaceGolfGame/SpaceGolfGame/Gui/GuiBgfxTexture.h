#pragma once
#include <CEGUI/CEGUI.h>
#include <bgfx/bgfx.h>

class GuiBgfxTexture : public CEGUI::Texture
{
	CEGUI::String name;
	CEGUI::Sizef size;
	bgfx::TextureHandle handle;
public:
	GuiBgfxTexture(CEGUI::String name);
	~GuiBgfxTexture();

	// Inherited via Texture
	virtual const CEGUI::String & getName() const override;
	virtual const CEGUI::Sizef & getSize() const override;
	virtual const CEGUI::Sizef & getOriginalDataSize() const override;
	virtual const CEGUI::Vector2f & getTexelScaling() const override;
	virtual void loadFromFile(const CEGUI::String & filename, const CEGUI::String & resourceGroup) override;
	virtual void loadFromMemory(const void * buffer, const CEGUI::Sizef & buffer_size, CEGUI::Texture::PixelFormat pixel_format) override;
	virtual void loadFromMemory(const bgfx::Memory *mem, const CEGUI::Sizef & buffer_size, bgfx::TextureFormat::Enum format);
	virtual void blitFromMemory(const void * sourceData, const CEGUI::Rectf & area) override;
	virtual void blitToMemory(void * targetData) override;
	virtual bool isPixelFormatSupported(const CEGUI::Texture::PixelFormat fmt) const override;
	void destroy();

	bgfx::TextureHandle getHandle() { return handle; }
};

