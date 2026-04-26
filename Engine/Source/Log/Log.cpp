#include "Log.h"

#include <memory>
#include <unordered_map>
#include <filesystem>
#include <chrono>
#include <source_location>
#include <concepts>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

using namespace GameEngine;
namespace fs = std::filesystem;

namespace
{
const std::unordered_map<LogVerbosity, spdlog::level::level_enum> c_verbosityMap =  //
    {{LogVerbosity::NoLogging, spdlog::level::off},                                 //
        {LogVerbosity::Display, spdlog::level::info},                               //
        {LogVerbosity::Warning, spdlog::level::warn},                               //
        {LogVerbosity::Error, spdlog::level::err},                                  //
        {LogVerbosity::Log, spdlog::level::info},                                   //
        {LogVerbosity::Fatal, spdlog::level::critical}};

constexpr const char* c_logPattern = "[%H:%M:%S.%e] [%^%l%$] %v";
const fs::path c_logDirectory = "logs";
constexpr const char* c_logFilePrefix = "GameEngine";
constexpr const char* c_logFileExtension = "txt";
constexpr const char* c_timestampFormat = "{:%Y.%m.%d-%H.%M.%S}";
}

// pImpl

class Log::Impl
{
public:
    Impl() 
    {
        using namespace spdlog;

        const auto conseleSink = std::make_shared<sinks::stdout_color_sink_mt>();
        m_consoleLogger = std::make_unique<logger>("console", conseleSink);
        m_consoleLogger->set_pattern(c_logPattern);

        const auto fileSink = std::make_shared<sinks::basic_file_sink_mt>(makeLogFile().string(), true);
        m_fileLogger = std::make_unique<logger>("file", fileSink);
        m_fileLogger->set_pattern(c_logPattern);
    }

    void log(LogVerbosity verbosity, const std::string& massage)
    {
        const auto spdLevel = c_verbosityMap.at(verbosity);

        if (verbosity != LogVerbosity::Log && m_consoleLogger->should_log(spdLevel))
        {
            m_consoleLogger->log(spdLevel, massage);
        }

        if (m_fileLogger->should_log(spdLevel))
        {
            m_fileLogger->log(spdLevel, massage);
        }
        
        
        if (verbosity == LogVerbosity::Fatal)
        {
            PLATFORM_BREAK();
        }
    }

private: 
    std::unique_ptr<spdlog::logger> m_consoleLogger;
    std::unique_ptr<spdlog::logger> m_fileLogger;

    fs::path makeLogFile() const
    {
        std::error_code ec;
        fs::create_directory(c_logDirectory, ec);
        if (ec)
        {
            std::cerr << "Failed to create log directory: " << ec.message() << std::endl;
        }
        const auto now = std::chrono::system_clock::now();
        const auto nowSecond = std::chrono::floor<std::chrono::seconds>(now);
        const std::string timestamp = std::format(c_timestampFormat, nowSecond);
        const std::string logName = std::format("{}-{}.{}", c_logFilePrefix, timestamp, c_logFileExtension);

        return c_logDirectory / logName;
    }
};

// interface

Log::Log(): m_pImpl(std::make_unique<Impl>()) {}
Log::~Log() = default;

void Log::log(const LogCategory& category, LogVerbosity verbosity, const std::string& massage, bool showLocation,
        std::source_location location) const
{
    const std::string fmtMsg =
        showLocation ? std::format("[{}] [{}:{}] {}", category.name(), location.function_name(), location.line(), massage)
        : std::format("[{}] {}", category.name(), massage);
    m_pImpl->log(verbosity, fmtMsg);
}

