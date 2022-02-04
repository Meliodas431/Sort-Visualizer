#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string_view>

class Application {
private:
    GLFWwindow* window;

public:
    Application(const uint32_t& Width, const uint32_t& Height, std::string_view title);
    ~Application();

    void Run();
};