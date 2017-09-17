#include "RenderTexture.h"
#include <bgfx_utils.h>

#include <iostream>

RenderTexture::RenderTexture(std::string path)
{
	handle = loadTexture(path.c_str());
    std::cout << "Loading texture " << path << std::endl;
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
	bgfx::destroy(handle);
}