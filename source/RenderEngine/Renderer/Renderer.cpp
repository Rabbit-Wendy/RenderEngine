#include "Renderer.h"

using namespace RE;

void RE::Renderer::BeginScene()
{
}

void RE::Renderer::EndScene()
{
}

void RE::Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
{
    vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}
