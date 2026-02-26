#pragma once

#include "Core.h"
#include "Event.h"

namespace RE
{ 
	class RE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer") : m_DebugName(name) {}
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:
		std::string m_DebugName;  //仅用于调试，不要实际使用
	};
}