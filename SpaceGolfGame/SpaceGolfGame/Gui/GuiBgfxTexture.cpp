#include "GuiBgfxTexture.h"
#include <bgfx/bgfx.h>
#include <bgfx_utils.h>
#include <entry/entry.h>
#include <bimg/decode.h>

using namespace CEGUI;

GuiBgfxTexture::GuiBgfxTexture(String name)
{
	this->name = name;
	handle = BGFX_INVALID_HANDLE;
}


GuiBgfxTexture::~GuiBgfxTexture()
{
}

const String & GuiBgfxTexture::getName() const
{
	return name;
}

const Sizef & GuiBgfxTexture::getSize() const
{
	return size;
}

const Sizef & GuiBgfxTexture::getOriginalDataSize() const
{
	return size;
}

const Vector2f & GuiBgfxTexture::getTexelScaling() const
{
	return texel;
}

void GuiBgfxTexture::loadFromFile(const String & filename, const String & resourceGroup)
{
    RawDataContainer fileContainer;
    CEGUI::System::getSingleton().getResourceProvider()->loadRawDataContainer(filename, fileContainer, resourceGroup);
    void* dataPtr = fileContainer.getDataPtr();
    int size = fileContainer.getSize();
    
    bimg::ImageContainer *imageContainer = bimg::imageParse(entry::getAllocator(), dataPtr, size);
    handle = bgfx::createTexture2D(
        imageContainer->m_width,
        imageContainer->m_height,
        imageContainer->m_numMips > 1,
        imageContainer->m_numLayers,
        bgfx::TextureFormat::Enum(imageContainer->m_format),
        BGFX_TEXTURE_NONE,
        bgfx::makeRef(imageContainer->m_data, imageContainer->m_size));
    bgfx::setName(handle, filename.c_str());
	setSize(Sizef(imageContainer->m_width, imageContainer->m_height));
    char tmp[100];
    sprintf(tmp, "[BgfxRenderer::GuiBgfxTexture::loadFromFile] Loading texture from file (Resource group %s): %s %dx%d", resourceGroup.c_str(), filename.c_str(), imageContainer->m_width, imageContainer->m_height);
    CEGUI::Logger::getSingleton().logEvent(tmp);
    CEGUI::System::getSingleton().getResourceProvider()->unloadRawDataContainer(fileContainer);
}

void GuiBgfxTexture::loadFromMemory(const void * buffer, const Sizef & buffer_size, PixelFormat pixel_format)
{
	setSize(buffer_size);
    char tmp[200];
    sprintf(tmp, "[BgfxRenderer::GuiBgfxTexture::loadFromMemory] Loading from memory: %dx%d", (int)buffer_size.d_width, (int)buffer_size.d_height);
    CEGUI::Logger::getSingleton().logEvent(tmp);
	long bytes;
	bgfx::TextureFormat::Enum format;
	switch (pixel_format) {
	case PixelFormat::PF_RGB:
		format = bgfx::TextureFormat::RGB8;
		bytes = buffer_size.d_width * buffer_size.d_height * 3;
		break;
	case PixelFormat::PF_RGBA:
		format = bgfx::TextureFormat::RGBA8;
		bytes = buffer_size.d_width * buffer_size.d_height * 4;
		break;
	default:
		CEGUI_THROW(RendererException("Unsupported pixel format"));
	}
	destroy();
	data = new unsigned char[bytes];
	memcpy(data, buffer, bytes);
	auto mem = bgfx::makeRef(data, bytes);
	loadFromMemory(mem, buffer_size, format);
}

void GuiBgfxTexture::loadFromMemory(const bgfx::Memory* mem, const Sizef & buffer_size, bgfx::TextureFormat::Enum format)
{
	handle = bgfx::createTexture2D(
		uint16_t(buffer_size.d_width)
		, uint16_t(buffer_size.d_height)
		, false
		, 1
		, format
		, 0
		, mem
	);
}

void GuiBgfxTexture::blitFromMemory(const void * sourceData, const Rectf & area)
{
	bgfx::updateTexture2D(handle, 0, 0,
		area.d_min.d_x, area.d_min.d_y,
		area.d_max.d_x - area.d_min.d_x, area.d_max.d_y - area.d_min.d_y,
		bgfx::makeRef(sourceData, size.d_width * size.d_height));
}

void GuiBgfxTexture::blitToMemory(void * targetData)
{
	bgfx::readTexture(handle, targetData);
}

bool GuiBgfxTexture::isPixelFormatSupported(const PixelFormat fmt) const
{
	return true;
}

void GuiBgfxTexture::destroy()
{
	if (handle.idx != bgfx::kInvalidHandle) {
		bgfx::destroy(handle);
		delete[] data;
	}
}
void GuiBgfxTexture::setSize(const CEGUI::Sizef& value)
{
    size = value;
    texel = Vector2f(1.0f / size.d_width, 1.0f / size.d_height);
}
