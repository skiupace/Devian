#pragma once
#include "GLObject.hpp"
#include <Core/Buffer.hpp>

namespace DEVIAN {
	namespace GL {
		class GLUniformBuffer : GLObject {
		public:
			void Create(uint32_t);
			void Update(const DEVIAN::BufferData&);
			void Destroy();

		private:

		};
	}
}
