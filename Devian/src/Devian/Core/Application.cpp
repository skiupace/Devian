#include <iostream>
#include <Platform/WindowsPlatform.hpp>
#include "Application.hpp"

namespace DEVIAN {
	Application::Application(const ApplicationSpecs& specs) {
		#if defined(_WIN32) || defined(_WIN64)
			m_Platform = new WindowsPlatformLayer();
			m_Platform->CreateNativeWindow(specs.width, specs.height, specs.title.c_str());
			m_NativeWindowHandle = m_Platform->GetNativeWindowHandle();
		#else
			#error This Engine is Currently Supports Windows Platform Only!
		#endif
	}

	bool Application::IsRunning() noexcept {
		return !glfwWindowShouldClose((GLFWwindow*)m_NativeWindowHandle);
	}

	void Application::Run() {
		try {
			while (IsRunning()) {
				m_Platform->RenderWindow();
				m_Platform->PollEvents();
			}
		} catch (const std::exception& ex) {
			std::cerr << ex.what() << std::flush;
			return;
		}
	}

	Application& Application::Get() {
		static Application instance;
		return instance;
	}

	PlatformLayer* Application::GetPlatformLayer() {
		return m_Platform;
	}

	void Application::SetWindowSizeCallBack(void(*callBackFunction)(GLFWwindow*, int, int)) {
		glfwSetWindowSizeCallback((GLFWwindow*)m_NativeWindowHandle, callBackFunction);
	}

	void Application::SetKeyboardCallBack(void(*callBackFunction)(GLFWwindow*, int, int, int, int)) {
		//callBackFunction(static_cast<KeyCode>(glfwGetKey(m_NativeWindowHandle, GLFW_KEY_F)));
		glfwSetKeyCallback((GLFWwindow*)m_NativeWindowHandle, callBackFunction);
	}

	Application::~Application() {
		glfwDestroyWindow((GLFWwindow*)m_NativeWindowHandle);
		glfwTerminate();

		delete m_Platform;
		m_Platform = nullptr;
		m_NativeWindowHandle = nullptr;
	}
}