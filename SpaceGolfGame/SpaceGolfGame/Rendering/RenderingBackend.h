#pragma once

#include <vector>
#include <stdint.h>
#include <string>
#include <bgfx/bgfx.h>
#include "../utilities.h"
#include "RenderingData.h"
#include "RenderManager.h"
using namespace Debug;

/////////////////////////
// CREATE INDEX BUFFER //
/////////////////////////
template <typename IndexBufferType, typename IndexType>
void createIndexBuffer(std::vector<IndexType> indices, IndexBufferType& handle);

template<typename IndexType>
void createIndexBuffer(std::vector<IndexType> indices, bgfx::IndexBufferHandle& handle) {
//    p(PrintSeverity::PRINT_DEBUG, "Generating index buffer of %d indices", indices.size());
    handle = bgfx::createIndexBuffer(bgfx::copy(indices.data(), indices.size() * sizeof(uint16_t)));
};

//////////////////////////
// CREATE VERTEX BUFFER //
//////////////////////////
template <typename VertexBufferType, typename VertexType>
void createVertexBuffer(std::vector<VertexType> vertices, VertexBufferType& handle);

template <typename VertexType>
void createVertexBuffer(std::vector<VertexType> vertices, bgfx::VertexBufferHandle& handle) {
//    p(PrintSeverity::PRINT_DEBUG, "Generating static vertex buffer of %d vertices", vertices.size());
    handle = bgfx::createVertexBuffer(bgfx::copy(vertices.data(), vertices.size() * sizeof(VertexType)), vertexDeclaration<VertexType>());
}

template <typename VertexType>
void createVertexBuffer(std::vector<VertexType> vertices, bgfx::DynamicVertexBufferHandle& handle) {
//    p(PrintSeverity::PRINT_DEBUG, "Generating dynamic vertex buffer of %d vertices", vertices.size());
    handle = bgfx::createDynamicVertexBuffer(bgfx::copy(vertices.data(), vertices.size() * sizeof(VertexType)), vertexDeclaration<VertexType>());
}

//////////////////////////
// MODIFY VERTEX BUFFER //
//////////////////////////
template <typename VertexBufferType, typename VertexType>
void modifyVertexBuffer(std::vector<VertexType>& vertices, VertexBufferType handle);

template <typename VertexType>
void modifyVertexBuffer(std::vector<VertexType>& vertices, bgfx::DynamicVertexBufferHandle handle) {
    bgfx::updateDynamicVertexBuffer(handle, 0, bgfx::copy(vertices.data(), vertices.size() * sizeof(VertexType)));
}

template <typename VertexType>
void modifyVertexBuffer(std::vector<VertexType>& vertices, bgfx::VertexBufferHandle handle) {
    p(PrintSeverity::PRINT_ERROR, "Tried to modify static vertex buffer: %d", handle.idx);
}

////////////////////////////
// RENDERING BACKEND BASE //
////////////////////////////
class RenderingBackendBase
{
public:
    virtual void render() = 0;
    virtual void destroy() = 0;
    virtual ~RenderingBackendBase() {
    }
};

///////////////////////
// RENDERING BACKEND //
///////////////////////
template <typename IndexBufferType, typename VertexBufferType, typename VertexType>
class RenderingBackend {
protected:
    IndexBufferType indexHandle;
    VertexBufferType vertexHandle;
    
    void useIndexBuffer() {
        bgfx::setIndexBuffer(indexHandle);
    }
    void useVertexBuffer() {
        bgfx::setVertexBuffer(0, vertexHandle);
    }
public:
    std::vector<uint16_t> indices;
    std::vector<VertexType> vertices;
    virtual void render() {
    }
    virtual void destroy() {
        bgfx::destroy(indexHandle);
        bgfx::destroy(vertexHandle);
    }
    virtual ~RenderingBackend() {
    }
    RenderingBackend(std::vector<uint16_t> indexValues, std::vector<VertexType> vertexValues) {
        createIndexBuffer(indexValues, indexHandle);
        createVertexBuffer(vertexValues, vertexHandle);
        indices = indexValues;
        vertices = vertexValues;
    }
    void setVertexValue(unsigned index, VertexType vertex) {
        vertices[index] = vertex;
        updateVertices();
    }
    void updateVertices() {
        modifyVertexBuffer(vertices, vertexHandle);
    }
};

//////////////////////////////////////
// SINGLE PROGRAM RENDERING BACKEND //
//////////////////////////////////////
template <typename IndexBufferType, typename VertexBufferType, typename VertexType>
class SingleProgramRenderingBackend : public RenderingBackend<IndexBufferType, VertexBufferType, VertexType> {
    bgfx::ProgramHandle program;
	uint64_t renderState;
public:
    SingleProgramRenderingBackend(std::vector<uint16_t> indexValues, std::vector<VertexType> vertexValues, std::string vShader, std::string fShader, uint64_t renderState) :
            RenderingBackend<IndexBufferType, VertexBufferType, VertexType>(indexValues, vertexValues) {
        program = RenderManager::get().getProgram(vShader, fShader);
        this->renderState = renderState;
    }
    
    virtual void render() override {
        RenderingBackend<IndexBufferType, VertexBufferType, VertexType>::useIndexBuffer();
        RenderingBackend<IndexBufferType, VertexBufferType, VertexType>::useVertexBuffer();
        bgfx::setState(renderState);
        bgfx::submit(0, program);
    }
    virtual void destroy() override {
        RenderingBackend<IndexBufferType, VertexBufferType, VertexType>::destroy();
    }
    virtual ~SingleProgramRenderingBackend() {
    }
};

/////////////////////////////
// SOLID RENDERING BACKEND //
/////////////////////////////
template <typename IndexBufferType, typename VertexBufferType>
class SolidRenderingBackend : public SingleProgramRenderingBackend<IndexBufferType, VertexBufferType, Pos2fColorVertex> {
public:
    SolidRenderingBackend(std::vector<uint16_t> indexValues, std::vector<Pos2fColorVertex> vertexValues, uint64_t renderState) :
            SingleProgramRenderingBackend<IndexBufferType, VertexBufferType, Pos2fColorVertex>(indexValues, vertexValues, "vs_only_color", "fs_only_color", renderState) {
    }
    virtual void render() override {
        SingleProgramRenderingBackend<IndexBufferType, VertexBufferType, Pos2fColorVertex>::render();
    }
    virtual void destroy() override {
        SingleProgramRenderingBackend<IndexBufferType, VertexBufferType, Pos2fColorVertex>::destroy();
    }
    virtual ~SolidRenderingBackend() {}
};

////////////////////////////////
// TEXTURED RENDERING BACKEND //
////////////////////////////////
template <typename IndexBufferType, typename VertexBufferType>
class TexturedRenderingBackend : public SingleProgramRenderingBackend<IndexBufferType, VertexBufferType, Pos2fColorTextureVertex> {
    bgfx::TextureHandle texture;
    bgfx::UniformHandle uniform;
public:
    TexturedRenderingBackend(std::vector<uint16_t> indexValues, std::vector<Pos2fColorTextureVertex> vertexValues, std::string texturePath, uint64_t renderState) :
            SingleProgramRenderingBackend<IndexBufferType, VertexBufferType, Pos2fColorTextureVertex>(indexValues, vertexValues, "vs_textured", "fs_textured", renderState) {
        uniform = RenderManager::get().getUniform("s_texture0", bgfx::UniformType::Int1);
        texture = RenderManager::get().getTexture(texturePath);
    }
    virtual void render() override {
        bgfx::setTexture(0, uniform, texture);
        SingleProgramRenderingBackend<IndexBufferType, VertexBufferType, Pos2fColorTextureVertex>::render();
    }
    virtual void destroy() override {
        SingleProgramRenderingBackend<IndexBufferType, VertexBufferType, Pos2fColorTextureVertex>::destroy();
    }
    virtual ~TexturedRenderingBackend(){}
};
