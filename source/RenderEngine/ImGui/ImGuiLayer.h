#pragma once

#include "Layer.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#include "ApplicationEvent.h"

namespace RE
{

	class RE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		bool onMouseLButtonDownEvent(MouseLButtonDownEvent& event);
        bool onMouseLButtonUpEvent(MouseLButtonUpEvent& event);
        bool onMouseRButtonDownEvent(MouseRButtonDownEvent& event);
        bool onMouseRButtonUpEvent(MouseRButtonUpEvent& event);
        bool onMouseMovedEvent(MouseMovedEvent& event);
        bool onMouseScrolledEvent(MouseScrolledEvent& event);

		bool onKeyPressedEvent(KeyPressedEvent& event);
        bool onKeyReleasedEvent(KeyReleasedEvent& event);
        bool onKeyTypedEvent(KeyTypedEvent& event);

        bool onWindowResizeEvent(WindowResizeEvent& event);
        bool onWindowCloseEvent(WindowCloseEvent& event);

		float m_Time = 0.0f;

	};

}




