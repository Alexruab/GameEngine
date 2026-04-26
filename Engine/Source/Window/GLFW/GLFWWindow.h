#pragma once

#include <string>
#include <functional>

class GLFWwindow;

namespace GameEngine
{

struct WindowId
{
    unsigned int value{0};
    constexpr explicit WindowId(unsigned int id) : value(id) {}

    constexpr WindowId operator++(int)
    { 
        WindowId temp = *this;
        ++value;
        return temp;
    }

    constexpr auto operator<=> (const WindowId& other) const = default;
};

struct WindowSettings
{
    std::string title{};
    int width{800};
    int height{600};
    int x{50};
    int y{50};
};

class GLFWWindow final
{
public:
    GLFWWindow(const WindowSettings& settings);
    ~GLFWWindow();

    bool isValid() const;

    bool shouldClose() const;

    void setTitle(const std::string& title);

private:
    GLFWwindow* m_window{nullptr};
};

 // namespace std

}  // namespace GameEngine

namespace std
{
template <>
struct hash<GameEngine::WindowId>
{
    std::size_t operator()(const GameEngine::WindowId& id) const noexcept { return std::hash<unsigned int>{}(id.value); }
};
} 