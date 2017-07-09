#include "RenderTexture.h"
#include <bgfx_utils.h>

RenderTexture::RenderTexture(std::string path)
{
	handle = loadTexture(path.c_str());
}

void RenderTexture::use(bgfx::UniformHandle sampler)
{
	bgfx::setTexture(0, sampler, handle);
}

RenderTexture::~RenderTexture()
{
}

void RenderTexture::destroy()
{
	bgfx::destroyTexture(handle);
}