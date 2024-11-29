#pragma once
#include <Renderer/GraphicsContext.hpp>
#include <Platform/Platform.hpp>
#include <Core/Input.hpp>
#include <functional>
#include <memory>

#include <Platform/GL/GLUniformBuffer.hpp>
#include <Platform/GL/GLVertexArray.hpp>
#include <Platform/GL/GLShader.hpp>
#include <Renderer/Camera3D.hpp>

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
		GraphicsAPI api = OPENGL;
	};

	using WindowSizeCallBackFuncPtr = std::function<void(int, int)>;
	using KeyboardCallBackFuncPtr = std::function<void(KeyCode)>;

	class Application {
	public:
		Application() = default;
		Application(const ApplicationSpecs& specs);
		~Application();

		inline bool IsRunning() noexcept;
		virtual void Run();

		void SetWidth(uint32_t);
		void SetHeight(uint32_t);

		static Application& Get();
		PlatformLayer* GetPlatformLayer();
		ApplicationSpecs GetApplicationSpecs();

		virtual void ExecuteScript() {}

		virtual void SetWindowSizeCallBack(const WindowSizeCallBackFuncPtr& func);
		virtual void SetKeyboardCallBack(const KeyboardCallBackFuncPtr& func);

		WindowSizeCallBackFuncPtr GetWindowSizeCallBack();
		KeyboardCallBackFuncPtr GetKeyboardCallBack();

	protected:
		// CallBacks
		WindowSizeCallBackFuncPtr m_WindowSizeCallBackFuncPtr = nullptr;
		KeyboardCallBackFuncPtr m_KeyboardCallBackFuncPtr = nullptr;

	private:
		ApplicationSpecs m_AppSpecs;
		std::unique_ptr<PlatformLayer> m_Platform;
		std::unique_ptr<GraphicsContext> m_GraphicsContext;

		inline static Application* m_Instance;

		Camera3D m_Camera;
		GL::GLShader Shader;
		GL::GLVertexArray QuadVertexArray;
		GL::GLUniformBuffer CameraUnifromBuffer;

	private:
		float m_DeltaTime = 0.0f;
		float m_LastTime = 0.0f;
	};

	Application* CreateApplication();
}