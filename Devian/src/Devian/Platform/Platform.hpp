#pragma once
#include <stdint.h>
#include <string>

namespace DEVIAN {
	class PlatformLayer {
	public:
		PlatformLayer() = default;
		virtual ~PlatformLayer() {}

		virtual void CreateWindow(const uint32_t, const uint32_t, const char*) {}
		virtual void* GetNativeWindowHandle() { return nullptr; }

		virtual void PollEvents() {}
		virtual void Render() {}
	};
}