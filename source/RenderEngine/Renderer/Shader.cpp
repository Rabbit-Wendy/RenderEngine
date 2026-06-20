#include "Shader.h"
#include "Renderer.h"
#include "../Platform/OpenGL/OpenGLShader.h"

using namespace RE;

Shader* RE::Shader::Create(const std::string vertexSrc, const std::string fragmentSrc)
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
        return new OpenGLShader(vertexSrc, fragmentSrc);
        break;
    default:
    {
        RE_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
    break;
    }
}