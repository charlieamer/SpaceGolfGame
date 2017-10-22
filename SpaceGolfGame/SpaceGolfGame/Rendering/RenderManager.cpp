#include "RenderManager.h"
#include <bgfx_utils.h>
#include "../utilities.h"

using namespace Debug;

RenderManager::RenderManager()
{
    p(PrintSeverity::PRINT_DEBUG, "Render manager created");
}

void RenderManager::destroy()
{
    destroyPrograms();
    destroyTextures();
    destroyUniforms();
}

void RenderManager::destroyPrograms()
{
    for (auto& program : programCache) {
        bgfx::destroy(program.second);
        p(PrintSeverity::PRINT_INFO, "Destroyed program %s, %s", program.first.first.c_str(), program.first.second.c_str());
    }
    programCache.clear();
}

void RenderManager::destroyTextures()
{
    for (auto& texture : textureCache) {
        bgfx::destroy(texture.second);
        p(PrintSeverity::PRINT_INFO, "Destroyed texture %s", texture.first.c_str());
    }
    textureCache.clear();
}

void RenderManager::destroyUniforms()
{
    for (auto& uniform : uniformCache) {
        bgfx::destroy(uniform.second);
        p(PrintSeverity::PRINT_INFO, "Destroyed uniform %s", uniform.first.c_str());
    }
    uniformCache.clear();
}

bgfx::ProgramHandle RenderManager::getProgram(std::string vShader, std::string fShader)
{
    auto pa = make_pair(vShader, fShader);
    if (programCache.count(pa) == 0) {
        programCache[pa] = loadProgram(vShader.c_str(), fShader.c_str());
        p(PrintSeverity::PRINT_INFO, "Created program %s, %s", vShader.c_str(), fShader.c_str());
    }
    return programCache[pa];
}

bgfx::TextureHandle RenderManager::getTexture(std::string path)
{
    if (textureCache.count(path) == 0) {
        textureCache[path] = loadTexture(path.c_str());
        p(PrintSeverity::PRINT_INFO, "Created texture %s", path.c_str());
    }
    return textureCache[path];
}

bgfx::UniformHandle RenderManager::getUniform(std::string name, bgfx::UniformType::Enum type)
{
    if (uniformCache.count(name) == 0) {
        uniformCache[name] = bgfx::createUniform(name.c_str(), type);
        p(PrintSeverity::PRINT_INFO, "Created uniform %s", name.c_str());
    }
    return uniformCache[name];
}

void RenderManager::setUniformVec4f(std::string name, Vector3f value)
{
    this->setUniformVec4f(name, value.x, value.y, value.z, 0);
}

void RenderManager::setUniformVec4f(std::string name, float a, float b, float c, float d)
{
    float vals[] = {a, b, c, d};
    bgfx::setUniform(getUniform(name, bgfx::UniformType::Vec4), vals);
}

void RenderManager::setUniformMat16f(std::string name, float* data)
{
    bgfx::setUniform(getUniform(name, bgfx::UniformType::Mat4), data);
}
