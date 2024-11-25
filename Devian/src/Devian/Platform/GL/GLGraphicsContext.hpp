#pragma once
#include <Renderer/GraphicsContext.hpp>

namespace DEVIAN {
	namespace GL {
		class GLGraphicsContext : public GraphicsContext {
		public:
			virtual void Init(void*) override;
			virtual void SwapBuffers(void*) override;
		};
	}
}
