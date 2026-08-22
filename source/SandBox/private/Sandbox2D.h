#pragma once

#include "RenderEngine.h"
#include "OrthoGraphicCameraController.h"

namespace RE
{
    class Sandbox2D : public Layer
    {
    public:
        Sandbox2D();
        virtual ~Sandbox2D() = default;
        virtual void OnAttach() override;
        virtual void OnDetach() override;
        void OnUpdate(TimeStep ts) override;
        void OnImGuiRender() override;
        void OnEvent(Event& e) override;

    private:
        OrthoGraphicCameraController m_CameraController;

        //¡Ÿ ±
        RE::Ref<VertexArray> m_SquareVA;
        ShaderLibrary m_ShaderLibrary;
        RE::Ref<Shader> m_FlatColorShader;

        glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1 };
    };
}