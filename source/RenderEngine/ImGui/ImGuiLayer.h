#pragma once

#include "Layer.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#include "ApplicationEvent.h"


namespace RE
{

	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() override;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

    private:
			float m_time = 0.0f;

	};

}




