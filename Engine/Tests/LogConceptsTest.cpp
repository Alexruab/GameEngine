#include "Log/Log.h"
#include <gtest/gtest.h>

using namespace GameEngine;

TEST(LogConceptTest, LogCategoryUsage)
{
    LogCategory category1("TestCategory");
    EXPECT_EQ(category1.name(), "TestCategory");

    LogCategory category2("AnotherTestCategory");
    EXPECT_EQ(category2.name(), "AnotherTestCategory");
    EXPECT_NE(category1.name(), category2.name());


}

TEST(LogConceptTest, LogCategoryTypeShouldBeValid)
{
    static_assert(ValidLogCategory<LogCategory>);
    static_assert(ValidLogCategory<const LogCategory&>);
}

TEST(LogConceptTest, LogMassegeTypeShouldBeValid)
{
    static_assert(LoggableMassege<std::string>);
    static_assert(LoggableMassege<const std::string&>);
    static_assert(LoggableMassege<std::string_view>);
    static_assert(LoggableMassege<const std::string_view&>);
    static_assert(LoggableMassege<const char*>);

    static_assert(!LoggableMassege<int>);
    static_assert(!LoggableMassege<float>);
    static_assert(!LoggableMassege<void*>);
    static_assert(!LoggableMassege<bool>);
}

TEST(LogConceptTest, LogVerbosityShouldBeValid)
{
    static_assert(ValidLogVerbosityLevel<LogVerbosity::NoLogging>);
    static_assert(ValidLogVerbosityLevel<LogVerbosity::Display>);
    static_assert(ValidLogVerbosityLevel<LogVerbosity::Warning>);
    static_assert(ValidLogVerbosityLevel<LogVerbosity::Error>);
    static_assert(ValidLogVerbosityLevel<LogVerbosity::Fatal>);
    static_assert(ValidLogVerbosityLevel<LogVerbosity::Log>);
}