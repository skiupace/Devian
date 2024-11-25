#pragma once

namespace DEVIAN {
	class GraphicsContext {
	public:
		virtual void Init(void* NativeWindowHandle) {}
		virtual void SwapBuffers(void* NativeWindowHandle) {}
	};
}