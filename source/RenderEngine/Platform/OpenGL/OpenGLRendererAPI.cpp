#include "OpenGLRendererAPI.h"

using namespace RE;

void RE::OpenGLRendererAPI::Init()
{
	glEnable(GL_BLEND); //允许混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //设置混合模式

	//glEnable(GL_DEPTH_TEST); //允许深度测试
}

void RE::OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
{
	glViewport(x, y, width, height);
}

void RE::OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
{
	glClearColor(0.1, 0.1, 0.1, 0.1);
}

void RE::OpenGLRendererAPI::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RE::OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
}
