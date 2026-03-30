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


	}

	void OnEvent(Event& e) override
	{
		//RE_LOG_CLIENT_TRACE("{0}", e.ToString());
		if (Input::IsKeyPressed(RE_KEY_L))
		{
			RE_LOG_CLIENT_TRACE("L");
		}
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





