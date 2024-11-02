#pragma once

#include <UI/DevianUI.hpp>
#include <GLFW/glfw3.h>
#include "Platform.hpp"

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

		//! Debugging Method.
		//x GLenum glCheckError_(const char*, int);

		//! Expermental Method.
		static void MousePositionCallback(GLFWwindow*, double, double);

		virtual void CreateWindow(const uint32_t, const uint32_t, const char*) override;
		virtual void* GetNativeWindowHandle() override;

		virtual void PollEvents() override;
		virtual void RenderWindow() override;

	private:
		void* m_NativeWindowHandle;
		DevianUI* m_DevianUI;
	};
}