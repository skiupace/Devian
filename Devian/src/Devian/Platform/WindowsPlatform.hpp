#pragma once
#include "Platform.hpp"

#include <UI/DevianUI.hpp>
#include <GLFW/glfw3.h>
#include <memory>

#ifndef IS_GLFW_INCLUDED
	#ifdef GLFW_VERSION_MAJOR
		#define IS_GLFW_INCLUDED true
	#endif // !GLFW_VERSION_MAJOR
#endif // !IS_GLFW_INCLUDED

namespace DEVIAN {
	class WindowsPlatformLayer : public PlatformLayer {
	public:
		WindowsPlatformLayer();
		~WindowsPlatformLayer();

		//! Expermental Method.
		[[maybe_unused]] // It's called attribute specifier.
		static void MousePositionCallback(GLFWwindow*, double, double);

		//! GLFW Error Logging Method.
		static void ErrorCallBack(int error, const char*);

		virtual void CreateNativeWindow(const uint32_t, const uint32_t, const char*) override;
		virtual void* GetNativeWindowHandle() override;

		virtual void PollEvents() override;
		virtual void RenderWindow() override;

		virtual std::pair<uint32_t, uint32_t> GetWindowSize() override;

		virtual bool IsKeyPressed(int keyCode) override;
		virtual bool IsKeyReleased(int keyCode) override;
		virtual bool IsMouseButtonPressed(int mouseButton) override;
		virtual bool IsMouseButtonReleased(int mouseButton) override;

	private:
		std::unique_ptr<GLFWwindow*> m_NativeWindowHandle;
		std::unique_ptr<DevianUI> m_DevianUI;
	};
}