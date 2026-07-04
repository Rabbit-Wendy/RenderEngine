#pragma once

#include "GraphicsContext.h"
#include <glfw3.h>

namespace RE {

	class OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}