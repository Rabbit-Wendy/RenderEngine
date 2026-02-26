#pragma once

//目前做的是阻塞事件，事件发生后停止其他操作立即处理事件

#include "Core.h"
#include <string>
#include <functional>

namespace RE
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseLButtonDown, MouseLButtonUp, MouseRButtonDown, MouseRButtonUp, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication=BIT(0),
		EventCategoryInput		=BIT(1),
		EventCategoryKeyBoard	=BIT(2),
		EventCategoryMouse		=BIT(3),
		EventCategoryMouseButton=BIT(4),
	};

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;  //调试用
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); } //调试用，可以重写

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() == category;
		}
	
		bool m_Handled = false; //事件是否被处理了

	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) :m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType()) //检查当前事件
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}


	private:
		Event& m_Event;
	};


#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type"Event"; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
}