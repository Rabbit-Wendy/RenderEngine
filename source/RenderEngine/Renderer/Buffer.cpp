#include "Buffer.h"
#include "Renderer.h"
#include "Log.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"

using namespace RE;

Ref<VertexBuffer> RE::VertexBuffer::Create(float* vertices, uint32_t size)
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
        return std::make_shared<OpenGLVertexBuffer>(vertices, size);
    break;
    default:
    {
        RE_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
    break;
    }   
}

Ref<IndexBuffer> RE::IndexBuffer::Create(uint32_t* indices, uint32_t count)
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
		return std::make_shared<OpenGLIndexBuffer>(indices, count);
	break;
	default:
	{
		RE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
	break;
	}
}
