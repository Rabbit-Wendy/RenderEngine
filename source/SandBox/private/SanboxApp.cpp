#include "SanboxApp.h"
#include "Imgui.h"



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

	void OnImGuiRender() override
	{
		//ImGui::Begin("Test");
		//ImGui::Text("Hello World");
		//ImGui::End();
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
}

SanboxApp::~SanboxApp()
{
}

Application* CreateApplication()
{
	return new SanboxApp();
}





