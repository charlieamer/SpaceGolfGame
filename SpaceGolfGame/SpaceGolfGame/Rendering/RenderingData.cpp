#include "RenderingData.h"

template<> bgfx::VertexDecl vertexDeclaration<Pos2fColorVertex>()
{
    bgfx::VertexDecl ret;
    ret
        .begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .end();
    return ret;
};

template<>
bgfx::VertexDecl vertexDeclaration<Pos2fColorTextureVertex>()
{
    bgfx::VertexDecl ret;
    ret
        .begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
        .end();
    return ret;
};