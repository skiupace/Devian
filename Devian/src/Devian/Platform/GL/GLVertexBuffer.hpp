#pragma once
#include "GLObject.hpp"
#include <Core/Buffer.hpp>

namespace DEVIAN {
	namespace GL {
		enum class GLVertexBufferUsage { STATIC_DRAW, DYNAMIC_DRAW };

		class GLVertexBuffer : public GLObject {
		public:
			void Create();
			void Fill(const DEVIAN::BufferData&, GLVertexBufferUsage);
			void Destroy();
		};
	}
}
