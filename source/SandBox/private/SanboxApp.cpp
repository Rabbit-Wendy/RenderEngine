#include "SanboxApp.h"
#include "Imgui.h"
#include "Log.h"
#include "glm/gtc/matrix_transform.hpp"
#include "..\Platform\OpenGL\OpenGLShader.h"
#include <glm/gtc/type_ptr.hpp>

using namespace RE;

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)/*, m_SquarePosition(0.0f, 0.0f, 0.0f)*/
	{
		//*******************   彩色三角形  *******************
		float vertices[7 * 3] = {
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f,     0.0f, 1.0f, 1.0f, 1.0f,
		};
		unsigned int indices[3] = { 0, 1, 2 };

		RE::Ref<VertexBuffer> vertexBuffer;
		vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"} ,
			{ ShaderDataType::Float4, "a_Color"},
			//{ ShaderDataType::Float3, "a_Normal"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray = VertexArray::Create();
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		RE::Ref<IndexBuffer> indexBuffer;
		indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
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

		// -------- Shader   着色器 
		std::string vertexSrc = R"(
		#version 330 core
		layout (location = 0) in vec3 a_Position;
		layout (location = 1) in vec4 a_Color;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

        out vec3 v_Position;
        out vec4 v_Color;
		void main()
		{
            v_Position = a_Position;
            v_Color = a_Color;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader = Shader::Create(vertexSrc, fragmentSrc);

		//************************* 方形 ****************

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,    0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,    1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,    0.0f, 1.0f,
		};
		unsigned int squareIndices[6] = { 0, 1,2, 2, 3, 0 };

		RE::Ref<VertexBuffer> squareVertexBuffer;
		squareVertexBuffer = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		BufferLayout squareLayout = {
			{ ShaderDataType::Float3, "a_Position"} ,
			{ ShaderDataType::Float2, "a_TexCoord"} ,
		};
		squareVertexBuffer->SetLayout(squareLayout);
		m_SquareVA = VertexArray::Create();
		m_SquareVA->AddVertexBuffer(squareVertexBuffer);

		RE::Ref<IndexBuffer> squareIndexBuffer;
		squareIndexBuffer = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIndexBuffer); //仅仅是bind了一下
		// -------- Shader   着色器
		std::string flatColorShaderVertexSrc = R"(
		#version 330 core
		layout (location = 0) in vec3 a_Position;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

		void main()
		{
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
	)";

		std::string flatColorShaderFragmentSrc = R"(
		#version 330 core
		layout (location = 0) out vec4 color;
        
        uniform vec4 u_Color;

		void main()
		{
			color = u_Color;
		}
	)";

		m_FlatColorShader = Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		std::dynamic_pointer_cast<OpenGLShader>(m_FlatColorShader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_FlatColorShader)->UpLoadUniformFloat4("u_Color", m_SquareColor);

		std::string textureShaderVertexSrc = R"(
		#version 330 core
		layout (location = 0) in vec3 a_Position;
		layout (location = 1) in vec2 a_TexCoord;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_Transform;

		out vec2 v_TexCoord;

		void main()
		{
            v_TexCoord = a_TexCoord;
			gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
		}
	)";

		std::string textureShaderFragmentSrc = R"(
		#version 330 core
		layout (location = 0) out vec4 color;
        
        in vec2 v_TexCoord;

        uniform sampler2D u_Texture;

		void main()
		{
			color = texture(u_Texture, v_TexCoord);
		}
	)";

		m_TextureShader = Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc);
		m_Texture = Texture2D::Create("E:/C++practice/RenderEngine/asserts/textures/Checkerboard.png");
		m_ChernoLogoTexture = Texture2D::Create("E:/C++practice/RenderEngine/asserts/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<OpenGLShader>(m_TextureShader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_TextureShader)->UpLoadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(TimeStep ts) override
	{
		if (ts > 1e-5)
		{
			RE_LOG_CLIENT_TRACE("fps: {0}", 1 / ts);
		}

		//相机移动
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
		else if (Input::IsKeyPressed(RE_KEY_I))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
        else if (Input::IsKeyPressed(RE_KEY_P))
        {
            m_CameraRotation += m_CameraRotationSpeed * ts;
        }

		//物体移动
  //if (Input::IsKeyPressed(RE_KEY_W))
  //      {
  //          m_SquarePosition.y += m_SquareMoveSpeed * ts;
  //      }
  //      else if (Input::IsKeyPressed(RE_KEY_S))
  //      {
  //          m_SquarePosition.y -= m_SquareMoveSpeed * ts;
  //      }
  //      else if (Input::IsKeyPressed(RE_KEY_A))
  //      {
  //          m_SquarePosition.x -= m_SquareMoveSpeed * ts;
  //      }
  //      else if (Input::IsKeyPressed(RE_KEY_D))
  //      {
  //          m_SquarePosition.x += m_SquareMoveSpeed * ts;
  //      }
	    //glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);


		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();


		m_Camera.SetRotation(m_CameraRotation);
		m_Camera.SetPosition(m_CameraPosition);

		Renderer::BeginScene(m_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		//渲染一堆方形
		for (int j = 0;j < 10;j++)
		{
			for (int i = 0;i < 10;i++)
			{
				glm::vec3 pos = glm::vec3(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transformPos = glm::translate(glm::mat4(1.0f), pos) * scale;
				Renderer::Submit(m_FlatColorShader, m_SquareVA, transformPos);
			}
		}

		m_Texture->Bind();
		Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		Renderer::Submit(m_TextureShader, m_SquareVA, 
			 glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//渲染一个三角形
		//Renderer::Submit(m_Shader, m_VertexArray);


		Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
	}


private:
	RE::Ref<Shader> m_Shader;
	RE::Ref<VertexArray> m_VertexArray;

	RE::Ref<Shader> m_FlatColorShader, m_TextureShader;
	RE::Ref<VertexArray> m_SquareVA;
	RE::Ref<Texture2D> m_Texture;
	RE::Ref<Texture2D> m_ChernoLogoTexture;

	OrthoGraphicCamera m_Camera;
	glm::vec3 m_CameraPosition;
    float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 90.0f;

	//物体移动变量
	//glm::vec3 m_SquarePosition;
	//float m_SquareMoveSpeed = 5.0f;

	//颜色
	glm::vec4 m_SquareColor = glm::vec4(0.2f, 0.3f, 0.8f, 1.0f);
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





 