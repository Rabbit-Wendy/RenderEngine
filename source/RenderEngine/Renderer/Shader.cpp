#include "Shader.h"
#include "Renderer.h"
#include "../Platform/OpenGL/OpenGLShader.h"

using namespace RE;

Ref<Shader> RE::Shader::Create(const std::string& filepath)
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
        return std::make_shared<OpenGLShader>(filepath);
        break;
    default:
    {
        RE_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
    break;
    }
}

Ref<Shader> RE::Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
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
        return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        break;
    default:
    {
        RE_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
    break;
    }
}

void RE::ShaderLibrary::Add(const Ref<Shader>& shader)
{
    std::string name = shader->GetName();
    Add(name, shader);
}

Ref<Shader> RE::ShaderLibrary::Load(const std::string& filepath)
{
    auto shader = Shader::Create(filepath);
    Add(shader);
    return shader;
}

void RE::ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
{
    if (Exists(name))
    {
        RE_CORE_ERROR("Shader already exists!");
        return;
    }
    m_Shaders[name] = shader;
}

Ref<Shader> RE::ShaderLibrary::Load(const std::string& name, const std::string& filepath)
{
    auto shader = Shader::Create(filepath);
    Add(name, shader);
    return shader;
}

Ref<Shader> RE::ShaderLibrary::Get(const std::string& name)
{
    if (!Exists(name))
    {
        RE_CORE_ERROR("Shader does not exist!");
        return nullptr;
    }
    return m_Shaders[name];
}

bool RE::ShaderLibrary::Exists(const std::string& name) const
{
    return m_Shaders.find(name) != m_Shaders.end();
}
