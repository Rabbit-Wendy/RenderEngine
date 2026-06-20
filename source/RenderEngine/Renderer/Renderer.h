#pragma once

#include "RenderCommand.h"
#include "OrthoGraphicCamera.h"
#include "Shader.h"

namespace RE {

	class Renderer {
	public:
		static void BeginScene(OrthoGraphicCamera& camera);
        static void EndScene();
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static SceneData* m_SceneData;
	};
}