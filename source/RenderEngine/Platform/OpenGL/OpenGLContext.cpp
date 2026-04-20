#include "Core.h"
#include "OpenGLContext.h"
#include <glad.h>

using namespace RE;

RE::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
       : m_WindowHandle(windowHandle)
{
    RE_CORE_ASSERT(windowHandle, "Window handle is null!")
}

RE::OpenGLContext::~OpenGLContext()
{
}

void RE::OpenGLContext::Init()
{
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    RE_CORE_ASSERT(status, "Failed to initialize Glad!");
}

void RE::OpenGLContext::SwapBuffers()
{
    glfwSwapBuffers(m_WindowHandle);
}
