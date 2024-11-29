#pragma once
#include "GLObject.hpp"
#include <Core/Buffer.hpp>

namespace DEVIAN {
	namespace GL {
		enum class GLVertexBufferUsage { STATIC_DRAW, DYNAMIC_DRAW };

		class GLVertexBuffer : public GLObject {
		public:
			void Create();
			void Fill(const BufferData& buffer, GLVertexBufferUsage usage = GLVertexBufferUsage::STATIC_DRAW);
			void Destroy();
		};
	}
}
