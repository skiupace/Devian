#include "Application.hpp"

#include <iostream>
#include <GLFW/glfw3.h>
#include <Core/Core.hpp>
#include <Platform/WindowsPlatform.hpp>

#include <Platform/GL/GLCommands.hpp>
#include <Platform/GL/GLGraphicsContext.hpp>

namespace DEVIAN {
	Application::Application(const ApplicationSpecs& specs) : m_AppSpecs(specs) {
		#if defined(_WIN32) || defined(_WIN64)
			m_Instance = this;
			m_Platform = std::make_unique<WindowsPlatformLayer>();
			m_Platform->CreateNativeWindow(specs.width, specs.height, specs.title.c_str());
		#else
			#error This Engine is Currently Supports Windows Platform Only!
		#endif

		switch (specs.api) {
		case OPENGL:
			m_GraphicsContext = std::make_unique<GL::GLGraphicsContext>();
			m_GraphicsContext->Init(m_Platform->GetNativeWindowHandle());
			break;

		case VULKAN:
			DEVIAN_ASSERT_MSG(false, "Vulkan Not Supported Yet!");
			break;

		case NONE:
			DEVIAN_ASSERT_MSG(false, "Failed to specify garphics api");
		}
	}

	inline bool Application::IsRunning() noexcept {
		return !glfwWindowShouldClose(static_cast<GLFWwindow*>(m_Platform->GetNativeWindowHandle()));
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
		return *m_Instance;
	}

	PlatformLayer* Application::GetPlatformLayer() {
		return m_Platform.get();
	}

	ApplicationSpecs Application::GetApplicationSpecs() {
		return m_AppSpecs;
	}

	void Application::SetWidth(uint32_t width) {
		m_AppSpecs.width = width;
	}

	void Application::SetHeight(uint32_t height) {
		m_AppSpecs.width = height;
	}

	void Application::SetWindowSizeCallBack(const WindowSizeCallBackFuncPtr& func) {
		m_WindowSizeCallBackFuncPtr = func;
	}

	void Application::SetKeyboardCallBack(const KeyboardCallBackFuncPtr& func) {
		m_KeyboardCallBackFuncPtr = func;
	}

	WindowSizeCallBackFuncPtr Application::GetWindowSizeCallBack() {
		return m_WindowSizeCallBackFuncPtr;
	}

	KeyboardCallBackFuncPtr Application::GetKeyboardCallBack() {
		return m_KeyboardCallBackFuncPtr;
	}

	Application::~Application() {
		m_Instance = nullptr;
		m_Platform = nullptr;
	}
}