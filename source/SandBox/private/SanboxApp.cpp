#include "SanboxApp.h"
#include "E:\C++practice\RenderEngine\source\RenderEngine\ImGui\ImGuiLayer.h"

using namespace RE;

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		RE_LOG_CLIENT_TRACE("ExampleLayer::Update");
	}

	void OnEvent(Event& e) override
	{
		RE_LOG_CLIENT_TRACE("{0}", e.ToString());
	}
};




SanboxApp::SanboxApp()
{
	PushLayer(new ExampleLayer());
	PushOverlay(new ImGuiLayer());
}

SanboxApp::~SanboxApp()
{
}

Application* CreateApplication()
{
	return new SanboxApp();
}





