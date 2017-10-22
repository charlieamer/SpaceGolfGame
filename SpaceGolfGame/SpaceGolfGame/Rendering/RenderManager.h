#pragma once

#include <bgfx/bgfx.h>
#include <string>
#include <map>
#include <utility>

#include <vmath.h>

class RenderManager
{
    std::map<std::string, bgfx::TextureHandle> textureCache;
    std::map<std::string, bgfx::UniformHandle> uniformCache;
    std::map<std::pair<std::string, std::string>, bgfx::ProgramHandle> programCache;
    RenderManager();
public:
    static RenderManager& get() {
        static RenderManager* value = nullptr;
        if (!value) {
            value = new RenderManager();
        }
        return *value;
    }
    bgfx::ProgramHandle getProgram(std::string vShader, std::string fShader);
    bgfx::TextureHandle getTexture(std::string path);
    bgfx::UniformHandle getUniform(std::string name, bgfx::UniformType::Enum type);
    void setUniformVec4f(std::string name, Vector3f value);
    void setUniformVec4f(std::string name, float a, float b, float c, float d);
    void setUniformMat16f(std::string name, float* data);
    void destroy();
    void destroyPrograms();
    void destroyTextures();
    void destroyUniforms();
};

