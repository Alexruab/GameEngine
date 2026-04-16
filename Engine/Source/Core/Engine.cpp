#include "Engine.h"
#include "Log/Log.h"
#include <format>

using namespace GameEngine;

DEFINE_LOG_CATEGORY_STATIC(LogEngine);

Engine::Engine() 
{
    //std::cout << "initializing GameEngine, version  " << version() << std::endl;

    //Log::getInstance().log(LogEngine,GameEngine::LogVerbosity::Display,  //
        //std::format("initializing GameEngine, version: {}", version()));

    //Log::getInstance().log(LogEngine, GameEngine::LogVerbosity::Error, "Error example", true);
    //Log::getInstance().log(LogEngine,GameEngine::LogVerbosity::Warning, "Warning example");
    //Log::getInstance().log(LogEngine, GameEngine::LogVerbosity::Fatal, "Fatal example");
    //Log::getInstance().log(LogEngine, GameEngine::LogVerbosity::Log, "Log example");

    LE_LOG(LogEngine, Display, "initializing GameEngine, version: {}", version());

    LE_LOG_DEBUG(LogEngine, Error, "Error example");
    LE_LOG(LogEngine,Warning, "Warning example");
    //LE_LOG(LogEngine, Fatal, "Fatal example");
    LE_LOG(LogEngine, Log, "Log example");
}
