#pragma once
#include <Renderer/GraphicsContext.hpp>

namespace DEVIAN {
	namespace GL {
		class GLGraphicsContext : public DEVIAN::GraphicsContext {
		public:
			virtual void Init(void*) override;
			virtual void SwapBuffers(void*) override;
		};
	}
}
