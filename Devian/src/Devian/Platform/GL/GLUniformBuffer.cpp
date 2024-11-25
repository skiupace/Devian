#include "GLUniformBuffer.hpp"

#include <Core/Core.hpp>
#include <glad/glad.h>

namespace DEVIAN {
	namespace GL {
		void GLUniformBuffer::Create(uint32_t bindingpoint) {
			glGenBuffers(1, &m_Handle);
			DEVIAN_ASSERT_MSG(m_Handle, "failed to create buffer!");

			// bind as a uniform buffer
			glBindBufferBase(GL_UNIFORM_BUFFER, bindingpoint, m_Handle);
		}

		void GLUniformBuffer::Update(const DEVIAN::BufferData& buffer) {
			glNamedBufferData(m_Handle, buffer.GetSize(), buffer.GetData(), GL_DYNAMIC_DRAW);
		}

		void GLUniformBuffer::Destroy() {
			glDeleteBuffers(1, &m_Handle);
		}
	}
}
