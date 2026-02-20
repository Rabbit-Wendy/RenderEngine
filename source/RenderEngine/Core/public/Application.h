#pragma once

#include "Core.h"
#include "Window.h"

namespace RE
{
	class RE_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();

	protected:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
}


