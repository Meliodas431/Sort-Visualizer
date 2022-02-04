#include "Application.h"
#include "core/Renderer.h"
#include "core/ErrorCheck.h"
#include "core/text/Text.h"
#include "core/Input/Input.h"
#include "Visualizer/Visualizer.h"
#include "UI/Buttons.h"
#include "UI/Menu.h"

#include <map>

void WindowResize(GLFWwindow* window, int width, int height) {
    Renderer::WindowResize(width, height);
}

void MousePosition(GLFWwindow* window, double X, double Y) {
    Input::SetMousePosition(X, Y);
}

void MouseButtonPressed(GLFWwindow* window, int button, int action, int mode) {
    Input::ProcessInput(button, action, mode);
}

Application::Application(const uint32_t& Width, const uint32_t& Height, std::string_view title) {
    if (!glfwInit())
        std::cout << "Error" << std::endl;

    window = glfwCreateWindow(Width, Height, title.data() , NULL, NULL);
   
    if (!window) {
        glfwTerminate();
    }

    glfwSetFramebufferSizeCallback(window, WindowResize);
    glfwSetCursorPosCallback(window, MousePosition);
    glfwSetMouseButtonCallback(window, MouseButtonPressed);
    glfwMakeContextCurrent(window);
   
    if (glewInit() != GLEW_OK) {
        std::cout << "glew error" << std::endl;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glfwSwapInterval(1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Application::~Application() {
    glfwTerminate();
}

void Application::Run() {
    Renderer::Init();
    Text::Init();

    Menu menu;
    Array array(200);
    Visualizer visualizer(array);  

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        GLCall(glClearColor(0.2f, 0.2f, 0.2f, 1.f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer::BeginScene();
        menu.Draw();
        if (menu.menuState.m_reset) {
            array.ResetArray();
            visualizer.Reset();
        }
        else if (menu.menuState.m_play) {
            visualizer.CreateStates(menu.menuState.m_type);
            visualizer.Play();
        }
        else {
            visualizer.CreateGraph(0);
        }
        Renderer::EndScene();
        glfwSwapBuffers(window);  
    }  
}