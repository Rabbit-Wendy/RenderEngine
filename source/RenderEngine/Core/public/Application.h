#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "ApplicationEvent.h"
#include "ImGuiLayer.h"
#include "Shader.h"
#include "Buffer.h"

namespace RE
{
	class  Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
		virtual void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_application; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		static Application* s_application;

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
	};
}


