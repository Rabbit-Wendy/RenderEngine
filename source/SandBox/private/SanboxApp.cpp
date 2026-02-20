#include "SanboxApp.h"
#include "ApplicationEvent.h"
#include "glfw3.h"

using namespace RE;

SanboxApp::SanboxApp()
{
}

SanboxApp::~SanboxApp()
{
}

Application* CreateApplication()
{
	return new SanboxApp();
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