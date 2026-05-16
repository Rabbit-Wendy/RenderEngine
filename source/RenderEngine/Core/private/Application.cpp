#include "Application.h"
#include "Log.h"
#include "ApplicationEvent.h"
#include "Input.h"
#include "KeyCodes.h"
#include <glad.h>

using namespace RE;

Application* Application::s_application = nullptr;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
    switch (type)
    {
    case ShaderDataType::Float:    return GL_FLOAT;
    case ShaderDataType::Float2:   return GL_FLOAT;
    case ShaderDataType::Float3:   return GL_FLOAT;
    case ShaderDataType::Float4:   return GL_FLOAT;
    case ShaderDataType::Mat3:     return GL_FLOAT;
    case ShaderDataType::Mat4:     return GL_FLOAT;
    case ShaderDataType::Int:      return GL_INT;
    case ShaderDataType::Int2:     return GL_INT;
    case ShaderDataType::Int3:     return GL_INT;
    case ShaderDataType::Int4:     return GL_INT;
    case ShaderDataType::Bool:     return GL_BOOL;
    }
	RE_CORE_ASSERT(false, "Unknown ShaderDataType!");
	return 0;
}

Application::Application()
{
	s_application = this;

	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(RE_BIND_EVENT_FN(Application::OnEvent));
	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);

    float vertices[3 * 7] = {
	-0.5f, -0.5f, 0.0f, 1.0f,0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 1.0f,1.0f, 0.0f, 1.0f,
	 0.0f,  0.5f, 0.0f, 0.0f,1.0f, 1.0f, 1.0f,
	};
	unsigned int indices[3] = { 0, 1, 2 };

	m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	BufferLayout layout = { 
		{ ShaderDataType::Float3, "a_Position"} ,
        { ShaderDataType::Float4, "a_Color"},
	    //{ ShaderDataType::Float3, "a_Normal"}
	};

	m_VertexBuffer->SetLayout(layout);

	// ------- Vertexv Array  顶点数组
	glGenVertexArrays(1, &m_VertexArray);  //创建1个顶点数组对象,(VAO-Vertex Array Object), ID为m_VertexArray
	glBindVertexArray(m_VertexArray);  //设置为当前活跃的 VAO

	uint32_t index = 0;
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.GetComponentCount(), 
			ShaderDataTypeToOpenGLBaseType(element.Type), 
			element.Normalized ? GL_TRUE : GL_FALSE,
			layout.GetStride(), (const void*)element.Offset);

		index++;
	}




	m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));


#if 0  // 直接使用VAO和VBO
	// ------- Vertex Buffer  顶点缓冲
	glGenBuffers(1, &m_VertexBuffer);  //创建1个顶点缓冲对象(VBO-Vertex Buffer Object), ID为m_VertexBuffer
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer); //设置为当前活跃的 VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //将CPU中的vertices写入GPU中的当前的VBO

	// ------- Vertexv Array  顶点数组
	glGenVertexArrays(1, &m_VertexArray);  //创建1个顶点数组对象,(VAO-Vertex Array Object), ID为m_VertexArray
    glBindVertexArray(m_VertexArray);  //设置为当前活跃的 VAO
	glEnableVertexAttribArray(0);  //启用顶点属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); //告诉GPU如何解析顶点数据  //这两句是放在VAO中的解析规则
	//参数含义：顶点属性的索引, 顶点属性的浮点数个数,浮点数类型， 是否需要归一化, 顶点属性的步长, 顶点属性的起始位置	 

	// ------ Index Buffer   索引缓冲
    glGenBuffers(1, &m_IndexBuffer); //创建1个索引缓冲对象(IBO-Index Buffer Object), ID为m_IndexBuffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer); //设置为当前活跃的 IBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);  //将CPU中的indices写入GPU中的当前的IBO

#endif
	 
	// -------- Shader   着色器  ——很多显卡提供了默认的着色器
	std::string vertexSrc = R"(
		#version 330 core
		layout (location = 0) in vec3 a_Position;
		layout (location = 1) in vec4 a_Color;
        out vec3 v_Position;
        out vec4 v_Color;
		void main()
		{
            v_Position = a_Position;
            v_Color = a_Color;
			gl_Position = vec4(a_Position.x, a_Position.y, a_Position.z, 1.0);
		}
	)";

	std::string fragmentSrc = R"(
		#version 330 core
		layout (location = 0) out vec4 color;
        in vec4 v_Color;
		void main()
		{
			color = v_Color;
		}
	)";

	m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
}

Application::~Application()
{
}

void Application::Run()
{
	while (m_Running)
	{
		glClearColor(0.1, 0.1, 0.1, 0.1);
		glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->bind();
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

		for (Layer* layer : m_LayerStack)  //从栈底向上逐层渲染
		{
			layer->OnUpdate();
		}

        m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
		{
			layer->OnImGuiRender();
		}
        m_ImGuiLayer->End();

		//auto[x,y] = Input::GetMousePosition();
  //      RE_LOG_CORE_TRACE("{0},{1}", x, y);

		m_Window->OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(RE_BIND_EVENT_FN(Application::OnWindowClose));

	//尝试打印事件
	//RE_LOG_CORE_TRACE(e.ToString());

	//从栈顶向下处理事件
	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.m_Handled)
		{
			break;
		}
	}
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Application::PushOverlay(Layer* overlay)
{
	m_LayerStack.PushOverlay(overlay);
	overlay->OnAttach();
}


