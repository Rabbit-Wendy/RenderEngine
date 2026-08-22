#include "Sandbox2D.h"
#include "ImGui.h"
#include <glm/gtc/type_ptr.hpp>
#include "..\Platform\OpenGL\OpenGLShader.h"


using namespace RE;

Sandbox2D::Sandbox2D()
	: Layer("Sanbox2D"), m_CameraController(1.78, true)
{

}

void RE::Sandbox2D::OnAttach()
{
	float squareVertices[3 * 4] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.5f,  0.5f, 0.0f,
	-0.5f,  0.5f, 0.0f,
	};
	unsigned int squareIndices[6] = { 0, 1,2, 2, 3, 0 };

	RE::Ref<VertexBuffer> squareVertexBuffer;
	squareVertexBuffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
	BufferLayout squareLayout = {
		{ ShaderDataType::Float3, "a_Position"} ,
	};
	squareVertexBuffer->SetLayout(squareLayout);
	m_SquareVA = VertexArray::Create();
	m_SquareVA->AddVertexBuffer(squareVertexBuffer);

	RE::Ref<IndexBuffer> squareIndexBuffer;
	squareIndexBuffer = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIndexBuffer); //仅仅是bind了一下

	m_FlatColorShader = m_ShaderLibrary.Load("E:/C++practice/RenderEngine/asserts/shaders/FlatColor.glsl");
	std::dynamic_pointer_cast<OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<OpenGLShader>(m_FlatColorShader)->UpLoadUniformFloat4("u_Color", m_SquareColor);
}

void RE::Sandbox2D::OnDetach()
{
}

void RE::Sandbox2D::OnUpdate(TimeStep ts)
{
	RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	RenderCommand::Clear();

    m_CameraController.OnUpdate(ts);
    Renderer::BeginScene(m_CameraController.GetCamera());

	Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Renderer::EndScene();
}


void RE::Sandbox2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
}

void RE::Sandbox2D::OnEvent(Event& e)
{
    m_CameraController.OnEvent(e);
}
