#include "RenderCommand.h"
#include "../Platform/OpenGL/OpenGLRendererAPI.h"

using namespace RE;

RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();