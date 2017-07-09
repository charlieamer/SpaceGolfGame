#pragma once

#include <bgfx/bgfx.h>
#include <string>
#include <map>

class Shader
{
	bgfx::ProgramHandle handle;
	std::map<std::string, bgfx::UniformHandle> uniforms;
public:
	Shader(const char* vsName, const char* fsName);
	~Shader();
	void use();
	void addUniform(std::string name, bgfx::UniformType::Enum type, uint16_t num = 1);
	bgfx::UniformHandle getUniform(std::string name);
};

