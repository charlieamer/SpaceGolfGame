#pragma once

#include <string>
#include <bgfx/bgfx.h>
class RenderTexture
{
	bgfx::TextureHandle handle;
public:
	RenderTexture(std::string path);
	RenderTexture() {};
	void use(bgfx::UniformHandle sampler);
	~RenderTexture();
	void destroy();
};

