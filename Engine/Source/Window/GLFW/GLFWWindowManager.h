#pragma once

#include "GLFWWindow.h"
#include <memory>
#include <expected>

namespace GameEngine
{
class GLFWWindow;

enum WindowCreationError
{
    ManagerIsNotInitialized,
    CreationFailed,
    InvalidWindow
};


class GLFWWindowManager final
{
public:
    GLFWWindowManager();
    ~GLFWWindowManager();

    void update();

    std::expected<WindowId, WindowCreationError> createWindow(const WindowSettings& settings);

    bool areAllWindowsClosed() const;

    std::shared_ptr<GLFWWindow> getWindowById(WindowId id) const;

private:

    bool m_isInitialized{false};

    std::unordered_map<WindowId, std::shared_ptr<GLFWWindow>> m_windows;

    WindowId m_windowIdCounter{1};

    void cleanupCloseWindows();

};
}  // namespace GameEngine