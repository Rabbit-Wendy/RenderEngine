#pragma once

#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/logger.h"

namespace RE
{ 
	class RE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
	    static std::shared_ptr<spdlog::logger> s_CoreLogger;
	    static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define RE_LOG_CORE_TRACE(...)  RE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RE_LOG_CORE_INFO(...)  RE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RE_LOG_CORE_WARN(...)  RE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RE_LOG_CORE_ERROR(...)  RE::Log::GetCoreLogger()->error(__VA_ARGS__)

#define RE_LOG_CLIENT_TRACE(...)  RE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RE_LOG_CLIENT_INFO(...)  RE::Log::GetClientLogger()->info(__VA_ARGS__)
#define RE_LOG_CLIENT_WARN(...)  RE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RE_LOG_CLIENT_ERROR(...)  RE::Log::GetClientLogger()->error(__VA_ARGS__)





