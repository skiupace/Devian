#pragma once
#include <Platform/Platform.hpp>

namespace DEVIAN {
	struct ApplicationSpecs {
		uint32_t width;
		uint32_t height;
		std::string title;
		void* nativeWindowHandle;
	};

	class Application {
	public:
		Application(const ApplicationSpecs& specs);
		~Application();
		void Run() noexcept;

	private:
		ApplicationSpecs m_AppSpecs;
		PlatformLayer* m_Platform;
	};
}