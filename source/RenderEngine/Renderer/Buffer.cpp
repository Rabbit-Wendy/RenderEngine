#include "Buffer.h"
#include "Renderer.h"
#include "Log.h"
#include "../Platform/OpenGL/OpenGLBuffer.h"

using namespace RE;

VertexBuffer* RE::VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch (Renderer::GetAPI())
    {
    case RenderAPI::None:
    {
        RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
        return nullptr;
    }
    break;
    case RenderAPI::OpenGL:
        return new OpenGLVertexBuffer(vertices, size);
    break;
    default:
    {
        RE_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
    break;
    }   
}

IndexBuffer* RE::IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
	switch (Renderer::GetAPI())
	{
	case RenderAPI::None:
	{
		RE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
		return nullptr;
	}
	break;
	case RenderAPI::OpenGL:
		return new OpenGLIndexBuffer(indices, count);
	break;
	default:
	{
		RE_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
	break;
	}
}
