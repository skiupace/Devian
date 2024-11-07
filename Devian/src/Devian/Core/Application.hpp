#pragma once
#include <Platform/Platform.hpp>
#include <Platform/Key.hpp>
#include <GLFW/glfw3.h>

namespace DEVIAN {
	struct ApplicationSpecs {
		uint32_t width;
		uint32_t height;
		std::string title;
		void* nativeWindowHandle;
	};

	class Application {
	public:
		Application() = default;
		Application(const ApplicationSpecs& specs);
		~Application();

		bool IsRunning() noexcept;
		void Run();

		static Application& Get();
		PlatformLayer* GetPlatformLayer();

		void SetWindowSizeCallBack(void(*callBackFunction)(GLFWwindow*, int, int));
		void SetKeyboardCallBack(void(*callBackFunction)(GLFWwindow*, int, int, int, int));

	private:
		ApplicationSpecs m_AppSpecs;
		PlatformLayer* m_Platform;
		void* m_NativeWindowHandle;
	};
}