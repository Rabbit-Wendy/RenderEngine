#include "SanboxApp.h"
#include "ApplicationEvent.h"

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
	int a = 5;
	RE_LOG_CORE_ERROR("11111");
	RE_LOG_CLIENT_WARN(a);


	RE::WindowResizeEvent ee(1280, 720);
	RE_LOG_CORE_TRACE(ee.ToString());

	system("pause");
}