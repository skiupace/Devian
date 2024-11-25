#include "GLGraphicsContext.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Core/Core.hpp>

namespace DEVIAN {
	namespace GL {
		void GLGraphicsContext::Init(void* NativeWindowHandle) {
			// Make Context
			glfwMakeContextCurrent(static_cast<GLFWwindow*>(NativeWindowHandle));

			// Init Glad
			DEVIAN_ASSERT_MSG(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD");

			// Set Viewport
			int width;
			int height;

			glfwGetWindowSize((GLFWwindow*)NativeWindowHandle, &width, &height);
			glViewport(0, 0, width, height);
		}

		void GLGraphicsContext::SwapBuffers(void* NativeWindowHandle) {
			glfwSwapBuffers((GLFWwindow*)NativeWindowHandle);
		}
	}
}
