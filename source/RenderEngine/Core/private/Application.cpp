#include "Application.h"
#include "Log.h"
#include "ApplicationEvent.h"
#include "glfw3.h"
#include <glad.h>

using namespace RE;

Application* Application::s_application = nullptr;

Application::Application()
{
	s_application = this;

	m_Window = std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(RE_BIND_EVENT_FN(Application::OnEvent));
}

Application::~Application()
{
}

void Application::Run()
{
	while (m_Running)
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		for (Layer* layer : m_LayerStack)  //从栈底向上逐层渲染
		{
			layer->OnUpdate();
		}

		m_Window->OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(RE_BIND_EVENT_FN(Application::OnWindowClose));

	//尝试打印事件
	RE_LOG_CORE_TRACE(e.ToString());

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


