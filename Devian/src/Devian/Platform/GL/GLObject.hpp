#pragma once
#include <stdint.h>

namespace DEVIAN {
	namespace GL {
		class GLObject {
		public:
			GLObject() : m_Handle(0) {}
			uint32_t GetHandle() { return m_Handle; }
		protected:
			uint32_t m_Handle;
		};
	}
}
