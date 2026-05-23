#include "VertexArray.h"
#include "Renderer.h"
#include "../Platform/OpenGL/OpenGlVertexArray.h"

using namespace RE;

VertexArray* RE::VertexArray::Create()
{
    switch (Renderer::GetAPI())
    {
    case RendererAPI::API::None:
    {
        RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    }
    break;
    case RendererAPI::API::OpenGL:
        return new OpenGLVertexArray();
        break;
    default:
    {
        RE_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
    break;
    }
}