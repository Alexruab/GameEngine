#pragma once

#include "memory"
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
    std::string m_name;
};

class Log final : public NonCopyabel
{
public:
    static Log& getInstance()
    {
        static Log instance;
        return instance;
    }

    void log(const LogCategory& category, LogVerbosity verbosity, const std::string& massage) const;

private:
    Log();
    ~Log();

    class Impl;
    std::unique_ptr<Impl> m_pImpl;
};

#define DEFINE_LOG_CATEGORY_STATIC(logName)          \
    namespace                                        \
    {                                                \
    const GameEngine::LogCategory logName(#logName); \
    }

};  // namespace GameEngine
