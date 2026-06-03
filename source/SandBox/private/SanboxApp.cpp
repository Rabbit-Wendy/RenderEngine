#include "SanboxApp.h"
#include "Imgui.h"
#include "Log.h"


using namespace RE;

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)
	{
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

	virtual void OnUpdate(TimeStep ts) override
	{
		if (ts > 1e-5)
		{
			RE_LOG_CLIENT_TRACE("fps: {0}", 1 / ts);
		}

		if (Input::IsKeyPressed(RE_KEY_LEFT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}
		else if (Input::IsKeyPressed(RE_KEY_RIGHT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (Input::IsKeyPressed(RE_KEY_UP))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}
		else if (Input::IsKeyPressed(RE_KEY_DOWN))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		else if (Input::IsKeyPressed(RE_KEY_A))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
        else if (Input::IsKeyPressed(RE_KEY_D))
        {
            m_CameraRotation += m_CameraRotationSpeed * ts;
        }



		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();


		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition(m_CameraPosition);

		Renderer::BeginScene(m_Camera);


		Renderer::Submit(m_SquareShader, m_SquareVA);
		Renderer::Submit(m_Shader, m_VertexArray);


		Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
	}


private:
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<VertexArray> m_VertexArray;

	std::shared_ptr<Shader> m_SquareShader;
	std::shared_ptr<VertexArray> m_SquareVA;

	OrthoGraphicCamera m_Camera;
	glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 90.0f;
};




SanboxApp::SanboxApp()
{
	PushLayer(new ExampleLayer());
}

SanboxApp::~SanboxApp()
{
}

Application* CreateApplication()
{
	return new SanboxApp();
}





 