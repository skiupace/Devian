#include <iostream>
#include <Core/Core.hpp>
#include <Utils/FileWatch.hpp>
#include "WindowsPlatform.hpp"

namespace DEVIAN {
    #if IS_GLFW_INCLUDED
    WindowsPlatformLayer::WindowsPlatformLayer() : m_DevianUI(new DevianUI()), m_NativeWindowHandle(nullptr) {}

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

        m_NativeWindowHandle = std::make_unique<GLFWwindow*>(glfwCreateWindow(width, height, title, NULL, NULL));
        DEVIAN_ASSERT(m_NativeWindowHandle);

        glfwMakeContextCurrent(*m_NativeWindowHandle.get());
        glfwSwapInterval(1); // Enable vsync

        // Initilize ImGui Library.
        m_DevianUI->ImGuiInit(*m_NativeWindowHandle.get());

        //x glfwSetCursorPosCallback((GLFWwindow*)m_NativeWindowHandle, MousePositionCallback);
    }

    void* WindowsPlatformLayer::GetNativeWindowHandle() {
        return static_cast<void*>(*m_NativeWindowHandle.get());
    }

    void WindowsPlatformLayer::PollEvents() {
        glfwPollEvents();
    }

    void WindowsPlatformLayer::RenderWindow() {
        // Get elapsed time since program launch
        float time = static_cast<float>(glfwGetTime());

        // Vary color based on time
        float red = (std::sin(time * 0.5f) + 1.0f) / 2.0f;
        float green = (std::sin(time * 0.3f) + 1.0f) / 2.0f;
        float blue = (std::sin(time * 0.7f) + 1.0f) / 2.0f;

        // Set initial background color
        glClearColor(red, green, blue, 1.0f);

        // Clear the buffer with the initial color
        glClear(GL_COLOR_BUFFER_BIT);

        // Render The Engine UI.
        //m_DevianUI->RenderUI();

        filewatch::FileWatch<std::wstring> watch(
            LR"(C:\Dev\Projects\C++ Projects\Game Engine\Devian\Devian\Test)",
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
        glfwSwapBuffers(*m_NativeWindowHandle.get());
    }

    std::pair<uint32_t, uint32_t> WindowsPlatformLayer::GetWindowSize() {
        int width, height;
        glfwGetWindowSize(*m_NativeWindowHandle.get(), &width, &height);
        return { width, height };
    }

    bool WindowsPlatformLayer::IsKeyPressed(int keyCode) {
        return glfwGetKey(*m_NativeWindowHandle.get(), keyCode) == GLFW_PRESS;
    }

    bool WindowsPlatformLayer::IsKeyReleased(int keyCode) {
        return glfwGetKey(*m_NativeWindowHandle.get(), keyCode) == GLFW_RELEASE;
    }

    bool WindowsPlatformLayer::IsMouseButtonPressed(int mouseButton) {
        return glfwGetMouseButton(*m_NativeWindowHandle.get(), mouseButton) == GLFW_PRESS;
    }

    bool WindowsPlatformLayer::IsMouseButtonReleased(int mouseButton) {
        return glfwGetMouseButton(*m_NativeWindowHandle.get(), mouseButton) == GLFW_RELEASE;
    }

    WindowsPlatformLayer::~WindowsPlatformLayer() {
        glfwDestroyWindow(*m_NativeWindowHandle.release());
        glfwTerminate();

        m_DevianUI = nullptr;
        m_NativeWindowHandle = nullptr;
    }

    #else
        #error GLFW Has Not Been Included!
    #endif // !IS_GLFW_INCLUDED
}