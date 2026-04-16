#pragma once

#include "memory"
#include <source_location>
#include <format>
#include <string>
#include <string_view>
#include <concepts>
#include "Core/Utility.h"

namespace GameEngine
{
enum class LogVerbosity : uint8_t
{
    NoLogging = 0,
    Display,
    Warning,
    Error,
    Log,
    Fatal
};

struct LogCategory
{
    explicit LogCategory(const std::string& name) : m_name(name) {}
    std::string name() const { return m_name; }

private:
    const std::string m_name;
};



class Log final : public NonCopyabel
{
public:
    static Log& getInstance()
    {
        static Log instance;
        return instance;
    }

    void log(const LogCategory& category, LogVerbosity verbosity, const std::string& massage, bool showLocation = false,
        std::source_location location = std::source_location::current()) const;

private:
    Log();
    ~Log();

    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

constexpr LogVerbosity c_minVerbosity = LogVerbosity::Display;
constexpr LogVerbosity c_maxVerbosity = LogVerbosity::Fatal;

template <typename T>
concept ValidLogCategory = std::constructible_from<LogCategory, T>;

template <typename T>
concept LoggableMassege = std::convertible_to<T, std::string> || std::convertible_to<T, std::string_view>;

template <LogVerbosity V>
concept ValidLogVerbosityLevel = V == LogVerbosity::NoLogging //
|| V == LogVerbosity::Display //
|| V == LogVerbosity::Warning //
|| V == LogVerbosity::Error //
|| V == LogVerbosity::Log //
|| V == LogVerbosity::Fatal;

};  // namespace GameEngine

#define DEFINE_LOG_CATEGORY_STATIC(logName)          \
    namespace                                        \
    {                                                \
    const GameEngine::LogCategory logName(#logName); \
    }

#define  LE_LOG_IMPL(categoryName, verbosity, showLocation, formatStr, ...) \
    do \
    {\
        if constexpr (GameEngine::LogVerbosity::verbosity >= GameEngine::c_minVerbosity && GameEngine::LogVerbosity::verbosity <= c_maxVerbosity)\
        {\
            static_assert(GameEngine::ValidLogCategory<decltype(categoryName)>, "Category must be of type LogCategory");\
            static_assert(GameEngine::LoggableMassege<decltype(formatStr)>, "Massage type must be convertable to string");\
            static_assert(GameEngine::ValidLogVerbosityLevel<GameEngine::LogVerbosity::verbosity>, "Verbosity must be one of: NoLogging, Display, Warning, Error, Log, Fatal");\
            GameEngine::Log::getInstance().log(categoryName, GameEngine::LogVerbosity::verbosity, std::format(formatStr, __VA_ARGS__), showLocation);\
        }\
    }\
    while (0)

#define  LE_LOG(categoryName, verbosity, formatStr, ...) \
LE_LOG_IMPL(categoryName, verbosity, false, formatStr, __VA_ARGS__);

#define  LE_LOG_DEBUG(categoryName, verbosity, formatStr, ...) \
LE_LOG_IMPL(categoryName, verbosity, true, formatStr, __VA_ARGS__);