#pragma once
#include "Event.h"
#include <sstream>

namespace RE
{
	//键盘事件
	class  KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_keyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput)

	protected:
		KeyEvent(int keycode) :m_keyCode(keycode) {}

		int m_keyCode;  //按键编号
	};

	//键盘按下事件
	class  KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode)
			:KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent::" << m_keyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	};

	//键盘抬起事件
	class  KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode) {
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent::" << m_keyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	};

	//键盘输入事件
	class  KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			:KeyEvent(keycode) {
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent::" << m_keyCode;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyTyped)
	};
}