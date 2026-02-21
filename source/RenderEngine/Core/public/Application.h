#pragma once

#include "Core.h"
#include "Window.h"


#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

namespace RE
{
	class RE_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
		virtual void OnEvent(Event& e) {};

	protected:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
}


