#pragma once

#include <sstream>
#include "Event.h"


namespace RE
{
	//鼠标移动事件
	class RE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(double x, double y)
			:m_mouseX(x), m_mouseY(y)
		{}

		inline double GetMouseX() const { return m_mouseX; }
		inline double GetMouseY() const { return m_mouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent::" << GetMouseX() << "," << GetMouseY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse)

	private:
		double m_mouseX;
		double m_mouseY;
	};

	//鼠标滚轮事件
	class RE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(double x, double y)
			:m_offsetX(x), m_offsetY(y)
		{
		}
		inline double GetOffsetX() const { return m_offsetX; }
		inline double GetOffsetY() const { return m_offsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent::" << GetOffsetX() << ","<< GetOffsetY();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse)

	private:
		double m_offsetX;
		double m_offsetY;
	};

	//鼠标按键事件
	class RE_API MouseButtonEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryMouseButton)
	};

	class RE_API MouseLButtonDownEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MouseLButtonDown)
	};
	class RE_API MouseLButtonUpEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MouseLButtonUp)
	};
	class RE_API MouseRButtonDownEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MouseRButtonDown)
	};
	class RE_API MouseRButtonUpEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MouseRButtonUp)
	};
}