#pragma once

#include "RenderEngine.h"

namespace RE
{
	class SanboxApp : public Application
	{
	public:
		SanboxApp();
		~SanboxApp();

		virtual void Run() override;
	};

}

