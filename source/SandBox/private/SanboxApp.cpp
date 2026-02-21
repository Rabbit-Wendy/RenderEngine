#include "SanboxApp.h"
#include "ApplicationEvent.h"
#include "glfw3.h"

using namespace RE;

SanboxApp::SanboxApp()
{
	m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(SanboxApp::OnEvent));
}

SanboxApp::~SanboxApp()
{
}

Application* CreateApplication()
{
	return new SanboxApp();
}

void SanboxApp::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(SanboxApp::OnWindowClose));

	//³¢ÊÔ´òÓ¡ÊÂ¼þ
    RE_LOG_CORE_TRACE(e.ToString());
}

void SanboxApp::Run()
{
	//int a = 5;
	//RE_LOG_CORE_ERROR("11111");
	//RE_LOG_CLIENT_WARN(a);


	//RE::WindowResizeEvent ee(1280, 720);
	//RE_LOG_CORE_TRACE(ee.ToString());

	//system("pause");

	while (m_Running)
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		m_Window->OnUpdate();
	}
}

bool SanboxApp::OnWindowClose(WindowCloseEvent& e)
{
	m_Running = false;
	return true;
}