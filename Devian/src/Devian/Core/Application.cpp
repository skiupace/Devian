#include <iostream>
#include <GLFW/glfw3.h>
#include <Platform/WindowsPlatform.hpp>
#include "Application.hpp"

namespace DEVIAN {
	Application::Application(const ApplicationSpecs& specs) {
		#if defined(_WIN32) || defined(_WIN64)
			m_Platform = new WindowsPlatformLayer();
			m_Platform->CreateWindow(specs.width, specs.height, specs.title.c_str());
		#else
			#error This Engine is Currently Supports Windows Platform Only!
		#endif
	}

	void Application::Run() noexcept {
		try {
			while (true) {
				m_Platform->Render();
				m_Platform->PollEvents();
			}
		} catch (const std::exception& ex) {
			std::cerr << ex.what() << std::flush;
			return;
		}
	}

	Application::~Application() {
		delete m_Platform;
	}
}