#include "Application.h"
#include "Log.h"
#include "ApplicationEvent.h"
#include "Input.h"
#include "KeyCodes.h"
#include "Renderer.h"

using namespace RE;

Application* Application::s_application = nullptr;

Application::Application()
	:m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	s_application = this;

	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(RE_BIND_EVENT_FN(Application::OnEvent));
	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);


	/////////////////////   彩色三角形
    float vertices[3 * 7] = {
	-0.5f, -0.5f, 0.0f, 1.0f,0.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, 0.0f, 1.0f,1.0f, 0.0f, 1.0f,
	 0.0f,  0.5f, 0.0f, 0.0f,1.0f, 1.0f, 1.0f,
	};
	unsigned int indices[3] = { 0, 1, 2 };

	std::shared_ptr<VertexBuffer> vertexBuffer;
	vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
	BufferLayout layout = { 
		{ ShaderDataType::Float3, "a_Position"} ,
        { ShaderDataType::Float4, "a_Color"},
	    //{ ShaderDataType::Float3, "a_Normal"}
	};
	vertexBuffer->SetLayout(layout);
    m_VertexArray.reset(VertexArray::Create());
	m_VertexArray->AddVertexBuffer(vertexBuffer);

    std::shared_ptr<IndexBuffer> indexBuffer;
	indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_VertexArray->SetIndexBuffer(indexBuffer); //仅仅是bind了一下


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

        uniform mat4 u_ViewProjection;

        out vec3 v_Position;
        out vec4 v_Color;
		void main()
		{
            v_Position = a_Position;
            v_Color = a_Color;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

	////////////////// 方形

    float squareVertices[3 * 4] = {
		-0.75f, -0.75f, 0.0f,
		 0.75f, -0.75f, 0.0f,
		 0.75f,  0.75f, 0.0f,
		-0.75f,  0.75f, 0.0f,
	};
	unsigned int squareIndices[6] = { 0, 1,2, 2, 3, 0 };

	std::shared_ptr<VertexBuffer> squareVertexBuffer;
	squareVertexBuffer.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	BufferLayout squareLayout = {
		{ ShaderDataType::Float3, "a_Position"} ,
	};
	squareVertexBuffer->SetLayout(squareLayout);
	m_SquareVA.reset(VertexArray::Create());
	m_SquareVA->AddVertexBuffer(squareVertexBuffer);

	std::shared_ptr<IndexBuffer> squareIndexBuffer;
	squareIndexBuffer.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIndexBuffer); //仅仅是bind了一下
	// -------- Shader   着色器  ——很多显卡提供了默认的着色器
	std::string squareVertexSrc = R"(
		#version 330 core
		layout (location = 0) in vec3 a_Position;

        uniform mat4 u_ViewProjection;

        out vec3 v_Position;
		void main()
		{
            v_Position = a_Position;
			gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
		}
	)";

	std::string squareFragmentSrc = R"(
		#version 330 core
		layout (location = 0) out vec4 color;
		void main()
		{
			color = vec4(0.2f, 1.0f, 1.0f, 1.0f);
		}
	)";

	m_SquareShader.reset(new Shader(squareVertexSrc, squareFragmentSrc));


}

Application::~Application()
{
}

void Application::Run()
{
	while (m_Running)
	{

		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::Clear();


		m_Camera.SetRotation(45);
		m_Camera.SetPosition({ 0.5f, 0.0f, 0.0f });

		Renderer::BeginScene(m_Camera);


        Renderer::Submit(m_SquareShader, m_SquareVA);
        Renderer::Submit(m_Shader, m_VertexArray);


        Renderer::EndScene();



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


