#include <iostream>
#include <Core/Core.hpp>
#include <Utils/FileWatch.hpp>
#include "WindowsPlatform.hpp"

namespace DEVIAN {
    #if IS_GLFW_INCLUDED
    WindowsPlatformLayer::WindowsPlatformLayer() : m_NativeWindowHandle(nullptr), m_DevianUI(new DevianUI()) {}

    void WindowsPlatformLayer::MousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
        std::cout << "Mouse Position: (" << xpos << ", " << ypos << ")\n";
    }

    void WindowsPlatformLayer::ErrorCallBack(int error, const char* description) {
        std::cerr << "GLFW Error! " << error << ": " << description << std::endl;
    }

    void WindowsPlatformLayer::CreateNativeWindow(const uint32_t width, const uint32_t height, const char* title) {
        if (!glfwInit()) {
            std::cerr << "Failed To Initialize GLFW!" << std::flush;
            return;
        }

        //! Initilize GLFW debug context
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        //! Set GLFW Error CallBack
        glfwSetErrorCallback(ErrorCallBack);

        m_NativeWindowHandle = glfwCreateWindow(width, height, title, NULL, NULL);
        DEVIAN_ASSERT(m_NativeWindowHandle);

        glfwMakeContextCurrent((GLFWwindow*)m_NativeWindowHandle);
        glfwSwapInterval(1); // Enable vsync

        // Initilize ImGui Library.
        m_DevianUI->ImGuiInit(m_NativeWindowHandle);

        //x glfwSetCursorPosCallback((GLFWwindow*)m_NativeWindowHandle, MousePositionCallback);
    }

    void* WindowsPlatformLayer::GetNativeWindowHandle() {
        return m_NativeWindowHandle;
    }

    void WindowsPlatformLayer::PollEvents() {
        glfwPollEvents();
    }

    void WindowsPlatformLayer::RenderWindow() {
        // Set initial background color
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        // Clear the buffer with the initial color
        glClear(GL_COLOR_BUFFER_BIT);

        // Render The Engine UI.
        //m_DevianUI->RenderUI();

        filewatch::FileWatch<std::wstring> watch(
            LR"(Test\ss.txt)",
            [](const std::wstring& path, const filewatch::Event change_type) {
                std::wcout << path << L" : ";
                switch (change_type) {
                case filewatch::Event::added:
                    std::cout << "The file was added to the directory." << '\n';
                    break;
                case filewatch::Event::removed:
                    std::cout << "The file was removed from the directory." << '\n';
                    break;
                case filewatch::Event::modified:
                    std::cout << "The file was modified. This can be a change in the time stamp or attributes." << '\n';
                    break;
                case filewatch::Event::renamed_old:
                    std::cout << "The file was renamed and this is the old name." << '\n';
                    break;
                case filewatch::Event::renamed_new:
                    std::cout << "The file was renamed and this is the new name." << '\n';
                    break;
                };
            }
        );

        // Swap front and back buffers to display the result
        glfwSwapBuffers((GLFWwindow*)m_NativeWindowHandle);
    }

    std::pair<uint32_t, uint32_t> WindowsPlatformLayer::GetWindowSize() {
        int width, height;
        glfwGetWindowSize((GLFWwindow*)m_NativeWindowHandle, &width, &height);
        return { width, height };
    }

    bool WindowsPlatformLayer::IsKeyPressed(int keyCode) {
        return glfwGetKey((GLFWwindow*)m_NativeWindowHandle, keyCode) == GLFW_PRESS;
    }

    bool WindowsPlatformLayer::IsKeyReleased(int keyCode) {
        return glfwGetKey((GLFWwindow*)m_NativeWindowHandle, keyCode) == GLFW_RELEASE;
    }

    bool WindowsPlatformLayer::IsMouseButtonPressed(int mouseButton) {
        return glfwGetMouseButton((GLFWwindow*)m_NativeWindowHandle, mouseButton) == GLFW_PRESS;
    }

    bool WindowsPlatformLayer::IsMouseButtonReleased(int mouseButton) {
        return glfwGetMouseButton((GLFWwindow*)m_NativeWindowHandle, mouseButton) == GLFW_RELEASE;
    }

    WindowsPlatformLayer::~WindowsPlatformLayer() {
        glfwDestroyWindow((GLFWwindow*)m_NativeWindowHandle);
        glfwTerminate();

        delete m_DevianUI;
        m_NativeWindowHandle = nullptr;
        m_DevianUI = nullptr;
    }

    #else
        #error GLFW Has Not Been Included!
    #endif // !IS_GLFW_INCLUDED
}