#pragma once

#include <sstream>
#include "Event.h"


namespace RE
{
	//窗口关闭事件
	class RE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {};
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	//窗口大小改变事件
	class RE_API WindowResizeEvent : public Event
	{
	public:
        WindowResizeEvent(double wid, double hig)
			:m_width(wid), m_hight(hig)
		{
		}
		inline int GetWidth() const { return m_width; }
		inline int GetHight() const { return m_hight; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent::" << GetWidth() << "," << GetHight();
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		double m_width;
		double m_hight;
	};
}
