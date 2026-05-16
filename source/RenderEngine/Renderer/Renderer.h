#pragma once

namespace RE {
	enum RenderAPI {
		None,
		OpenGL,
		DirectX,
		Vulkan,
		Metal
	};

	class Renderer {
	public:
		static RenderAPI GetAPI() { return s_RendererAPI; }
	private:
		static RenderAPI s_RendererAPI;
	};
}