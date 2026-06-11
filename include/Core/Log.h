#pragma once

#include <memory>
#include <spdlog/spdlog.h>


#ifdef _WIN32
#define DEBUG_BREAK() __debugbreak()
#define DLL_EXPORT __declspec(dllexport)
#endif
#ifdef __linux__
#define DEBUG_BREAK() __builtin_trap()
#define DLL_EXPORT __attribute__((visibility("default")))

#endif
#ifdef __APPLE__
#define DEBUG_BREAK() __builtin_trap()
#define DLL_EXPORT __attribute__((visibility("default")))

#endif

#define ENGINE_LOG(...)    ::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ENGINE_WARN(...)   ::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ENGINE_ERROR(...)  ::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ENGINE_TRACE(...)  ::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define ENGINE_ASSERT(condition, ...) \
    do { \
        if (!(condition)) { \
            ENGINE_ERROR(__VA_ARGS__); \
            DEBUG_BREAK(); \
            ENGINE_ERROR("Assertion hit"); \
        } \
    } while (0)

namespace Log
{
    void Init();

    std::shared_ptr<spdlog::logger>& GetCoreLogger();
}