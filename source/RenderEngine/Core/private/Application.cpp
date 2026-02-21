#include "Application.h"

using namespace RE;

Application::Application()
{
}

Application::~Application()
{
}

void Application::Run()
{
	while (m_Running)
	{
        m_Window->OnUpdate();
	}
}

