#include <iostream>
#include <Core/Core.hpp>
#include "WindowsPlatform.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//x #include <vector>
//x #include <cmath>

namespace DEVIAN {
    #if IS_GLFW_INCLUDED
    //x std::vector<std::pair<float, float>> points;
    WindowsPlatformLayer::WindowsPlatformLayer() : m_NativeWindowHandle(nullptr) {}

    void WindowsPlatformLayer::MousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
        std::cout << "Mouse Position: (" << xpos << ", " << ypos << ")\n";

        #if false //! Demo Drawing App Code
        // Convert screen coordinates to OpenGL coordinates and store in points
        float x = (xpos / 900.0f) * 2.0f - 1.0f;
        float y = (1.0f - ypos / 600.0f) * 2.0f - 1.0f;

        if (!points.empty()) {
            // Calculate the distance between the last point and the new point
            auto& lastPoint = points.back();
            float distance = std::sqrt(std::pow(x - lastPoint.first, 2) + std::pow(y - lastPoint.second, 2));

            // Threshold distance to determine if interpolation is needed
            float threshold = 0.05f; // Adjust this value to control smoothness
            if (distance > threshold) {
                // Interpolate additional points between the last point and the new point
                int numSegments = static_cast<int>(distance / threshold);
                for (int i = 1; i < numSegments; ++i) {
                    float t = i / static_cast<float>(numSegments);
                    float interpX = lastPoint.first + t * (x - lastPoint.first);
                    float interpY = lastPoint.second + t * (y - lastPoint.second);
                    points.emplace_back(interpX, interpY);
                }
            }
        }

        points.emplace_back(x, y);  // Add point to the list
        #endif
    }

    void WindowsPlatformLayer::CreateWindow(const uint32_t width, const uint32_t height, const char* title) {
        if (!glfwInit()) {
            std::cerr << "Failed To Initialize GLFW!" << std::flush;
            return;
        }

        //! Initilize GLFW debug context
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        m_NativeWindowHandle = glfwCreateWindow(width, height, title, NULL, NULL);
        DEVIAN_ASSERT(m_NativeWindowHandle);

        glfwMakeContextCurrent((GLFWwindow*)m_NativeWindowHandle);
        glfwSwapInterval(1); // Enable vsync

        #if false //! Demo Drawing App Code
        // Set up orthographic projection (2D)
        glOrtho(-1, 1, -1, 1, -1, 1);

        // Set the mouse position callback
        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
            auto platform = static_cast<WindowsPlatformLayer*>(glfwGetWindowUserPointer(window));
            platform->MousePositionCallback(window, xpos, ypos);
        });

        glfwSetWindowUserPointer(window, this);
        #endif

        //x glfwSetCursorPosCallback((GLFWwindow*)m_NativeWindowHandle, MousePositionCallback);

        //! Initilize IMGUI To Use In The Engine UI.
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // IF using Docking Branch
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)m_NativeWindowHandle, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
        ImGui_ImplOpenGL3_Init();
    }

    void* WindowsPlatformLayer::GetNativeWindowHandle() {
        return m_NativeWindowHandle;
    }

    void WindowsPlatformLayer::PollEvents() {
        glfwPollEvents();
    }

    void WindowsPlatformLayer::Render() {
        // Set initial background color
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        // Clear the buffer with the initial color
        glClear(GL_COLOR_BUFFER_BIT);

        #if false //! Demo Drawing App Code
        // Set line width for thicker lines
        glLineWidth(5.0f); // Adjust this value for desired thickness

        // Set color to black for drawing points
        glColor3f(0.0f, 0.0f, 0.0f);

        // Draw a continuous line between points
        glBegin(GL_LINE_STRIP);
        for (const std::pair<float, float>& point : points)
            glVertex2f(point.first, point.second);
        glEnd();
        #endif

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        //ImGui::ShowDemoWindow(); // Show demo window! :)

        // TODO: Design And Make The Engine UI.
        //! Code Goes Here...

        // Rendering
        ImGui::Render();
        int displayWidth, displayHeight;

        ImGuiIO& io = ImGui::GetIO();
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        glfwGetFramebufferSize((GLFWwindow*)m_NativeWindowHandle, &displayWidth, &displayHeight);
        glViewport(0, 0, displayWidth, displayHeight);

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backupCurrentContext);
        }

        // Swap front and back buffers to display the result
        glfwSwapBuffers((GLFWwindow*)m_NativeWindowHandle);
    }

    WindowsPlatformLayer::~WindowsPlatformLayer() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow((GLFWwindow*)m_NativeWindowHandle);
        glfwTerminate();
        delete m_NativeWindowHandle;
    }

    #else
        #error GLFW Has Not Been Included!
    #endif // !IS_GLFW_INCLUDED
}