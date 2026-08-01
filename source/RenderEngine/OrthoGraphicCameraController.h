#pragma once

#include "OrthoGraphicCamera.h"
#include "TimeStep.h"
#include "ApplicationEvent.h"  //窗口调整事件
#include "MouseEvent.h"  //鼠标事件

namespace RE {
	class OrthoGraphicCameraController {
	public:
		OrthoGraphicCameraController(float aspectRatio, bool enableRotation = false);  // 长宽比，是否允许旋转

		void OnUpdate(TimeStep ts);
		void OnEvent(Event& e);
		OrthoGraphicCamera& GetCamera() { return m_Camera; }
		const OrthoGraphicCamera& GetCamera() const{ return m_Camera; }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);

	private:
		float m_AspectRatio;  // 长宽比
		float m_ZoomLevel = 1.0f;  //缩放比

		bool m_EnableRotation; //是否允许旋转

		OrthoGraphicCamera m_Camera;

        glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
        float m_CameraRotation = 0.0f;

        float m_CameraTranslationSpeed = 5.0f;
        float m_CameraRotationSpeed = 180.0f;
	};
}
