#include "GLFWWindowManager.h"
#include "GLFWWindow.h"
#include "Log/Log.h"
#include "GLFW/glfw3.h"

using namespace GameEngine;

DEFINE_LOG_CATEGORY_STATIC(LogGLFWWindowManager);

GLFWWindowManager::GLFWWindowManager() 
{
	glfwSetErrorCallback([](int errorCode, const char* description) {
		LE_LOG(LogGLFWWindowManager, Error, "GLFW Error {}: description: {}", errorCode, description); });

	 if (!glfwInit())
	 {
		 LE_LOG(LogGLFWWindowManager, Error, "Failed to initialize GLFW");
		 return;
     }

	 m_isInitialized = true;
     LE_LOG(LogGLFWWindowManager, Display, "GLFW initialized successfully");

	 

}

GLFWWindowManager::~GLFWWindowManager() 
{
    m_windows.clear();

    if (m_isInitialized)
	{
        glfwSetErrorCallback(nullptr);
		glfwTerminate();
		LE_LOG(LogGLFWWindowManager, Display, "GLFW terminated successfully");
    }
}

void GLFWWindowManager::update() 
{
    if (!m_isInitialized) return;

	glfwPollEvents();
    cleanupCloseWindows();
}

void GameEngine::GLFWWindowManager::cleanupCloseWindows()
{
    auto it = m_windows.begin();
    while (it != m_windows.end())
    {
        if (it->second->shouldClose())
        {
            LE_LOG(LogGLFWWindowManager, Display, "Window with ID {} closed and removed from manager", it->first.value);
            it = m_windows.erase(it);
            
            continue;
        }
        ++it;
    }
}

std::expected<WindowId, WindowCreationError> GLFWWindowManager::createWindow(const WindowSettings& settings)
{
    if (!m_isInitialized)
    {
        LE_LOG(LogGLFWWindowManager, Error, "Cannot create window. Failed to initialize GLFW");
        return std::unexpected(WindowCreationError::ManagerIsNotInitialized);
    }

	auto window = std::make_shared<GLFWWindow>(settings);

	if (!window->isValid())
    {
        LE_LOG(LogGLFWWindowManager, Error, "Failed to create window GLFW");
        return std::unexpected(WindowCreationError::InvalidWindow);
    }

    const WindowId id = m_windowIdCounter++;

    m_windows[id] = window;
    LE_LOG(LogGLFWWindowManager, Display, "Window created successfully with ID {}", id.value);

    return id;
}

bool GLFWWindowManager::areAllWindowsClosed() const
{
    return m_windows.empty();
}

std::shared_ptr<GLFWWindow> GLFWWindowManager::getWindowById(WindowId id) const
{
    const auto it = m_windows.find(id);
    return it != m_windows.end() ? it->second : nullptr;
}


