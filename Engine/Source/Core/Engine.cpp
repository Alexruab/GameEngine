#include "Engine.h"
#include "Log/Log.h"
#include <format>
#include "Window/GLFW/GLFWWindowManager.h"

using namespace GameEngine;

DEFINE_LOG_CATEGORY_STATIC(LogEngine);

Engine::Engine() 
{

    LE_LOG(LogEngine, Display, "initializing GameEngine, version: {}", version());

    m_windowManager = std::make_unique<GLFWWindowManager>();

    const auto windowResult = m_windowManager->createWindow(WindowSettings{});  // {"GameEngine", 800, 600, 50, 50}
    
    if (!windowResult)   
    {
        LE_LOG(LogEngine, Error, "Failed to create main window.");
        return;
    }

    if (auto window = m_windowManager->getWindowById(windowResult.value()))
    {
        window->setTitle(std::format("GameEngine, version: {}", version()));
    }

    m_initialized = true;
    
}

Engine::~Engine() = default;

void GameEngine::Engine::Run()
{
    if (!m_initialized)
    {
        LE_LOG(LogEngine, Error, "Failed to run the engine. Engine is not initialized.");
        return;
    }

    while (!m_windowManager->areAllWindowsClosed())
    {
        m_windowManager->update();
    }
}
