#include "GLIndexBuffer.hpp"

#include <glad/glad.h>
#include <Core/Core.hpp>

namespace DEVIAN {
	namespace GL {
		void GLIndexBuffer::Create() {
			glGenBuffers(1, &m_Handle);
			DEVIAN_ASSERT_MSG(m_Handle, "failed to create buffer!");
		}

		void GLIndexBuffer::Fill(const std::vector<uint32_t>& indices) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
		}

		void GLIndexBuffer::Destroy() {
			glDeleteBuffers(1, &m_Handle);
		}
	}
}
