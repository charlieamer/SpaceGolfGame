#include "Shader.h"
#include <bgfx_utils.h>


std::string Shader::getTextureName(int slot)
{
	char tmp[100];
	sprintf_s(tmp, 99, "s_texture%d", slot);
	return std::string(tmp);
}

Shader::Shader(const char* vsName, const char* fsName)
{
	handle = loadProgram(vsName, fsName);
}


Shader::~Shader()
{
	bgfx::destroyProgram(handle);
	for (auto& uniform : uniforms) {
		bgfx::destroyUniform(uniform.second);
	}
	for (auto& texture : textures) {
		bgfx::destroyTexture(texture.second);
	}
}

void Shader::use()
{
	for (auto& texture : textures) {
		bgfx::setTexture(texture.first, uniforms[getTextureName(texture.first)], texture.second);
	}
	bgfx::submit(0, handle);
}

void Shader::addUniform(std::string name, bgfx::UniformType::Enum type, uint16_t num)
{
	uniforms[name] = bgfx::createUniform(name.c_str(), type, num);
}

void Shader::addTexture(std::string path, int slot)
{
	auto handle = loadTexture(path.c_str());
	addUniform(getTextureName(slot), bgfx::UniformType::Int1);
	textures[slot] = handle;
}
