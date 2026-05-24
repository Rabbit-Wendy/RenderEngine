#include "Renderer.h"

using namespace RE;

Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

void RE::Renderer::BeginScene(OrthoGraphicCamera& camera)
{
	m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void RE::Renderer::EndScene()
{
}

void RE::Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
{
	shader->bind();
	shader->UpLoadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
    vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
