#include "Application.h"
#include "Log.h"
#include "ApplicationEvent.h"
#include "Input.h"
#include "KeyCodes.h"
#include "Renderer.h"
#include "glfw3.h"


using namespace RE;

Application* Application::s_application = nullptr;

Application::Application()
{
	s_application = this;

	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(RE_BIND_EVENT_FN(Application::OnEvent));
	m_Window->SetVSync(true);

	Renderer::Init();

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);
}

Application::~Application()
{
}

void Application::Run()
{
	while (m_Running)
	{
		float time = (float)glfwGetTime();
		TimeStep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;

		for (Layer* layer : m_LayerStack)  //从栈底向上逐层渲染
		{
			layer->OnUpdate(timestep);
		}

        m_ImGuiLayer->Begin();
		for (Layer* layer : m_LayerStack)
		{
			layer->OnImGuiRender();
		}
        m_ImGuiLayer->End();

		m_Window->OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(RE_BIND_EVENT_FN(Application::OnWindowClose));

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


