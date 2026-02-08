#pragma once

#include "Core.h"

namespace RE
{
	class RE_API Application
	{
	public:
		Application();
		virtual ~Application();

		virtual void Run();
	};
}


