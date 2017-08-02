#include "GuiBgfxRenderer.h"
#include "GuiBgfxGeometry.h"
#include "GuiBgfxTextureTarget.h"

#include <bgfx_utils.h>

void GuiBgfxRenderer::destroy()
{
	bgfx::destroyProgram(program);
	bgfx::destroyUniform(textureUniform);
}

GuiBgfxRenderer::GuiBgfxRenderer(const char* vsFileLocation, const char* fsFileLocation)
{
	targets.push_back(new GuiBgfxRenderTarget(*this));

	program = loadProgram(vsFileLocation, fsFileLocation);
	textureUniform = bgfx::createUniform("s_texture0", bgfx::UniformType::Int1);
}


GuiBgfxRenderer::~GuiBgfxRenderer()
{
}

RenderTarget & GuiBgfxRenderer::getDefaultRenderTarget()
{
	return *targets[0];
}

GeometryBuffer & GuiBgfxRenderer::createGeometryBuffer()
{
	GuiBgfxGeometry* ret = new GuiBgfxGeometry(*this);
	geometries.insert(ret);
	ret->setProgramHandle(program, textureUniform);
	return *ret;
}

void GuiBgfxRenderer::destroyGeometryBuffer(const GeometryBuffer & buffer)
{
	auto it = geometries.find((GuiBgfxGeometry*)&buffer);
	if (it == geometries.end()) {
		CEGUI_THROW(NullObjectException("Geometry to destroy was not found"));
	}
	(*it)->destroyBuffers();
	geometries.erase(it);
}

void GuiBgfxRenderer::destroyAllGeometryBuffers()
{
	for (auto val : geometries) {
		val->destroyBuffers();
		delete val;
	}
	geometries.clear();
}

TextureTarget * GuiBgfxRenderer::createTextureTarget()
{
	return nullptr;
}

void GuiBgfxRenderer::destroyTextureTarget(TextureTarget * target)
{
}

void GuiBgfxRenderer::destroyAllTextureTargets()
{
}

Texture & GuiBgfxRenderer::createTexture(const String & name)
{
	GuiBgfxTexture* ret = new GuiBgfxTexture(name);
	textures[name] = ret;
	return *ret;
}

Texture & GuiBgfxRenderer::createTexture(const String & name, const String & filename, const String & resourceGroup)
{
	GuiBgfxTexture *ret = (GuiBgfxTexture*)&createTexture(name);
	ret->loadFromFile(filename, resourceGroup);
	return *ret;
}

Texture & GuiBgfxRenderer::createTexture(const String & name, const Sizef & size)
{
	return createTexture(name);
}

void GuiBgfxRenderer::destroyTexture(Texture & texture)
{
	destroyTexture(texture.getName());
}

void GuiBgfxRenderer::destroyTexture(const String & name)
{
	if (textures.count(name) != 0) {
		textures[name]->destroy();
		delete textures[name];
		textures.erase(textures.find(name));
	}
}

void GuiBgfxRenderer::destroyAllTextures()
{
	for (auto pair : textures) {
		pair.second->destroy();
		delete pair.second;
	}
	textures.clear();
}

Texture & GuiBgfxRenderer::getTexture(const String & name) const
{
	return *textures.at(name);
}

bool GuiBgfxRenderer::isTextureDefined(const String & name) const
{
	return textures.count(name) > 0;
}

void GuiBgfxRenderer::beginRendering()
{
	unsigned char pass = 0;
	for (auto& target : targets) {
		if (typeid(*target) == typeid(GuiBgfxTextureTarget)) {
			target->setPassId(256 - targets.size() + pass++);
		}
		else {
			target->setPassId(1);
		}
	}
}

void GuiBgfxRenderer::endRendering()
{
}

void GuiBgfxRenderer::setDisplaySize(const Sizef & size)
{
	CEGUI_THROW(RendererException("Set display size not implemented"));
}

const Sizef & GuiBgfxRenderer::getDisplaySize() const
{
	return Sizef(bgfx::getStats()->width, bgfx::getStats()->height);
	// return Sizef(1, 1);
}

const Vector2f & GuiBgfxRenderer::getDisplayDPI() const
{
	return Vector2f(72, 72);
}

uint GuiBgfxRenderer::getMaxTextureSize() const
{
	auto caps = bgfx::getCaps();
	return caps->limits.maxTextureSize;
}

const String & GuiBgfxRenderer::getIdentifierString() const
{
	return "Bgfx Renderer";
}

void GuiBgfxRenderer::activateTarget(GuiBgfxRenderTarget * target)
{
	currentPass = target->getPassId();
}

void GuiBgfxRenderer::activateRenderTarget()
{
	activateTarget(*targets.begin());
}

uint8_t GuiBgfxRenderer::getCurrentPass()
{
	return currentPass;
}

