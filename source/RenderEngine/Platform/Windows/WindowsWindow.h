#pragma once

#include "Window.h"
#include <glfw3.h>
#include "GraphicsContext.h"

namespace RE 
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        virtual ~WindowsWindow();

        virtual void OnUpdate() override;

        virtual unsigned int GetWidth() const override { return m_Data.Width; }
        virtual unsigned int GetHeight() const override { return m_Data.Height; }

        virtual void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
        virtual void SetVSync(bool enabled) override;  //设置是否启用 V-Sync（Vertical Synchronization，垂直同步）
        //是一种将显卡输出帧率与显示器刷新率同步的技术，用于消除画面撕裂（screen tearing），但可能增加输入延迟或导致帧率不足时卡顿
        virtual bool IsVSync() const override;

        virtual void* GetNativeWindow() const override { return m_Window; }

    private:
        void Init(const WindowProps& props);
        void Shutdown();

        GLFWwindow* m_Window;
        GraphicsContext* m_Context;
        
        struct WindowData
        {
            std::string Title = "";
            unsigned int Width = 0; 
            unsigned int Height = 0;
            bool VSync = false;

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}