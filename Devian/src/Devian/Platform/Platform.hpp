#pragma once
#include <string>
#include <stdint.h>

namespace DEVIAN {
	class PlatformLayer {
	public:
		PlatformLayer() = default;
		virtual ~PlatformLayer() {}

		virtual void CreateNativeWindow(const uint32_t, const uint32_t, const char*) {}
		virtual void* GetNativeWindowHandle() { return nullptr; }

		virtual void PollEvents() {}
		virtual void RenderWindow() {}

		virtual std::pair<uint32_t, uint32_t> GetWindowSize() { return { 0, 0 }; }

		virtual bool IsKeyPressed(int keyCode) { return false; }
		virtual bool IsKeyReleased(int keyCode) { return false; }
		virtual bool IsMouseButtonPressed(int mouseButton) { return false; }
		virtual bool IsMouseButtonReleased(int mouseButton) { return false; }
	};
}