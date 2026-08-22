#include "OrthoGraphicCameraController.h"
#include "Input.h"
#include "KeyCodes.h"

using namespace RE;

OrthoGraphicCameraController::OrthoGraphicCameraController(float aspectRatio, bool enableRotation)
	: m_AspectRatio(aspectRatio), 
	m_EnableRotation(enableRotation),
	m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
{
}

void OrthoGraphicCameraController::OnUpdate(TimeStep ts)
{
	// Æ½ÒÆ
	if (Input::IsKeyPressed(RE_KEY_A))
	{
		m_CameraPosition.x += m_CameraTranslationSpeed * ts;
	}
	else if (Input::IsKeyPressed(RE_KEY_D))
	{
		m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
	}
	else if (Input::IsKeyPressed(RE_KEY_W))
	{
		m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
	}
	else if (Input::IsKeyPressed(RE_KEY_S))
	{
		m_CameraPosition.y += m_CameraTranslationSpeed * ts;
	}

	// Ðý×ª
    if (m_EnableRotation)
    {
        if (Input::IsKeyPressed(RE_KEY_Q))
        {
            m_CameraRotation -= m_CameraRotationSpeed * ts;
        }
        else if (Input::IsKeyPressed(RE_KEY_E))
        {
            m_CameraRotation += m_CameraRotationSpeed * ts;
        }
        m_Camera.SetRotation(m_CameraRotation);
    }

    m_Camera.SetPosition(m_CameraPosition);
	m_CameraTranslationSpeed = m_ZoomLevel * 0.5f;
}

void OrthoGraphicCameraController::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<MouseScrolledEvent>(RE_BIND_EVENT_FN(OrthoGraphicCameraController::OnMouseScrolled));
	dispatcher.Dispatch<WindowResizeEvent>(RE_BIND_EVENT_FN(OrthoGraphicCameraController::OnWindowResized));
}

bool OrthoGraphicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
{
	m_ZoomLevel -= e.GetOffsetY();
	m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}

bool OrthoGraphicCameraController::OnWindowResized(WindowResizeEvent& e)
{
	m_AspectRatio = (float)e.GetWidth() / (float)e.GetHight();
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
	return false;
}
