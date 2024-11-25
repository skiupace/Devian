#pragma once
#include <vector>
#include "GLObject.hpp"

namespace DEVIAN {
	namespace GL {
		class GLIndexBuffer : public GLObject {
		public:
			void Create();
			void Fill(const std::vector<uint32_t>&);
			void Destroy();
		};
	}
}
