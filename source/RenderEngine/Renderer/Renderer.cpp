#include "Renderer.h"
#include "..\Platform\OpenGL\OpenGLShader.h"

using namespace RE;

Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

void RE::Renderer::Init()
{
    RenderCommand::Init();
}

void RE::Renderer::BeginScene(OrthoGraphicCamera& camera)
{
	m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void RE::Renderer::EndScene()
{
}

void RE::Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
{
	shader->Bind();
	std::dynamic_pointer_cast<OpenGLShader>(shader)->UpLoadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
	std::dynamic_pointer_cast<OpenGLShader>(shader)->UpLoadUniformMat4("u_Transform", transform);
    vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
