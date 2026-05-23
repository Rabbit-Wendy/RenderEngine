#include "OpenGLRendererAPI.h"

using namespace RE;

void RE::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(0.1, 0.1, 0.1, 0.1);
}

void RE::OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RE::OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
