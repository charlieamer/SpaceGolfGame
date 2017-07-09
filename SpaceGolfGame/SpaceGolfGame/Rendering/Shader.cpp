#include "Shader.h"
#include <bgfx_utils.h>

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
}

void Shader::use()
{
	bgfx::submit(0, handle);
}

void Shader::addUniform(std::string name, bgfx::UniformType::Enum type, uint16_t num)
{
	uniforms[name] = bgfx::createUniform(name.c_str(), type, num);
}

bgfx::UniformHandle Shader::getUniform(std::string name)
{
	return uniforms[name];
}
