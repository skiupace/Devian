#pragma once
#include <Renderer/GraphicsContext.hpp>
#include <Platform/Platform.hpp>
#include <Platform/Key.hpp>
#include <GLFW/glfw3.h>
#include <functional>
#include <memory>

namespace DEVIAN {
	enum GraphicsAPI {
		NONE,
		OPENGL,
		VULKAN
	};

	struct ApplicationSpecs {
		uint32_t width;
		uint32_t height;
		std::string title;
		GraphicsAPI API = OPENGL;
	};

	using WindowSizeCallBackFuncPtr = std::function<void(int, int)>;
	using KeyboardCallBackFuncPtr = std::function<void(KeyCode)>;

	class Application {
	public:
		Application() = default;
		Application(const ApplicationSpecs& specs);
		~Application();

		inline bool IsRunning() noexcept;
		void Run();

		void SetWidth(uint32_t);
		void SetHeight(uint32_t);

		static Application& Get();
		PlatformLayer* GetPlatformLayer();
		ApplicationSpecs GetApplicationSpecs();

		void SetWindowSizeCallBack(const WindowSizeCallBackFuncPtr& func);
		void SetKeyboardCallBack(const KeyboardCallBackFuncPtr& func);

		WindowSizeCallBackFuncPtr GetWindowSizeCallBack();
		KeyboardCallBackFuncPtr GetKeyboardCallBack();

	private:
		ApplicationSpecs m_AppSpecs;
		std::unique_ptr<PlatformLayer> m_Platform;
		std::unique_ptr<GLFWwindow*> m_NativeWindowHandle;
		std::unique_ptr<GraphicsContext> m_GraphicsContext;

		// CallBacks
		WindowSizeCallBackFuncPtr m_WindowSizeCallBackFuncPtr = nullptr;
		KeyboardCallBackFuncPtr m_KeyboardCallBackFuncPtr = nullptr;

		inline static Application* m_Instance;
	};
}