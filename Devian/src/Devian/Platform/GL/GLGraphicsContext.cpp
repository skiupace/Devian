#include "GLGraphicsContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Core/Core.hpp>

namespace DEVIAN {
	namespace GL {
		void GLGraphicsContext::Init(void* NativeWindowHandle) {
			// Make Context
			glfwMakeContextCurrent((GLFWwindow*)NativeWindowHandle);

			// Init Glad
			DEVIAN_ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD");

			// Set Viewport
			int w, h;
			glfwGetWindowSize((GLFWwindow*)NativeWindowHandle, &w, &h);
			glViewport(0, 0, w, h);
		}

		void GLGraphicsContext::SwapBuffers(void* NativeWindowHandle) {
			glfwSwapBuffers((GLFWwindow*)NativeWindowHandle);
		}
	}
}
