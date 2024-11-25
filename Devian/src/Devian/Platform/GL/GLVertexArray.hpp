#pragma once
#include "GLVertexBuffer.hpp"
#include "GLIndexBuffer.hpp"

namespace DEVIAN {
	namespace GL {
		enum class GLShaderAttribType { FLOAT, INT };

		struct GLVertexAttrib {
			uint32_t ShaderLocation;
			uint32_t Count;
			GLShaderAttribType Type;
			uint32_t Offset;
		};

		class GLVertexArray : GLObject {
		public:
			void Create();
			void Destroy();

			void AddVertexBuffer(GLVertexBuffer&, uint32_t);
			void AddIndexBuffer(GLIndexBuffer&);
			void AddVertexAttrib(const GLVertexAttrib&, uint32_t);
			void Bind();
		private:
			std::vector<GLVertexBuffer> m_VertexBuffers;
		};
	}
}
