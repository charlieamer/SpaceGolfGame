#pragma once

#include <CEGUI/CEGUI.h>
#include <map>
#include <set>
#include <vector>
using namespace std;
#include "GuiBgfxGeometry.h"
#include "GuiBgfxTexture.h"
class GuiBgfxRenderTarget;

class GuiBgfxRenderer : public CEGUI::Renderer
{
	CEGUI::Rectf screenArea;
	CEGUI::Sizef screenSize;
	map<CEGUI::String, GuiBgfxTexture*> textures;
	set<GuiBgfxGeometry*> geometries;
	vector<GuiBgfxRenderTarget*> targets;
	uint8_t currentPass;

	bgfx::ProgramHandle program;
	bgfx::UniformHandle textureUniform;
public:
	void destroy();
	void updateScreenSize(int width, int height);

	GuiBgfxRenderer(const char* shaderLocation, const char* fsFileLocation);
	~GuiBgfxRenderer();

	// Inherited via Renderer
	virtual CEGUI::RenderTarget & getDefaultRenderTarget() override;
	virtual CEGUI::GeometryBuffer & createGeometryBuffer() override;
	virtual void destroyGeometryBuffer(const CEGUI::GeometryBuffer & buffer) override;
	virtual void destroyAllGeometryBuffers() override;
	virtual CEGUI::TextureTarget * createTextureTarget() override;
	virtual void destroyTextureTarget(CEGUI::TextureTarget * target) override;
	virtual void destroyAllTextureTargets() override;
	virtual CEGUI::Texture & createTexture(const CEGUI::String & name) override;
	virtual CEGUI::Texture & createTexture(const CEGUI::String & name, const CEGUI::String & filename, const CEGUI::String & resourceGroup) override;
	virtual CEGUI::Texture & createTexture(const CEGUI::String & name, const CEGUI::Sizef & size) override;
	virtual void destroyTexture(CEGUI::Texture & texture) override;
	virtual void destroyTexture(const CEGUI::String & name) override;
	virtual void destroyAllTextures() override;
	virtual CEGUI::Texture & getTexture(const CEGUI::String & name) const override;
	virtual bool isTextureDefined(const CEGUI::String & name) const override;
	virtual void beginRendering() override;
	virtual void endRendering() override;
	virtual void setDisplaySize(const CEGUI::Sizef & size) override;
	virtual const CEGUI::Sizef & getDisplaySize() const override {
		return screenSize;
	};
	virtual const CEGUI::Rectf & getDisplayArea() const {
		return screenArea;
	}
	virtual const CEGUI::Vector2f & getDisplayDPI() const override;
	virtual CEGUI::uint getMaxTextureSize() const override;
	virtual const CEGUI::String & getIdentifierString() const override;

	void activateTarget(GuiBgfxRenderTarget* target);
	void activateRenderTarget();
	uint8_t getCurrentPass();
};

