#pragma once

#include "RenderEngine.h"
#include "ApplicationEvent.h"

namespace RE
{
	class SanboxApp : public Application
	{
	public:
		SanboxApp();
		~SanboxApp();

		virtual void Run() override;
		virtual void OnEvent(Event& e) override;

	private:
		bool OnWindowClose(WindowCloseEvent& e);
	};

}

