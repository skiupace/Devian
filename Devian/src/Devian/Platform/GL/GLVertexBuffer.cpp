#include "GLVertexBuffer.hpp"

#include <glad/glad.h>
#include <Core/Core.hpp>

namespace DEVIAN {
	GLenum ToGL(DEVIAN::GL::GLVertexBufferUsage usage) {
		switch (usage) {
		case DEVIAN::GL::GLVertexBufferUsage::STATIC_DRAW: return GL_STATIC_DRAW;
		case DEVIAN::GL::GLVertexBufferUsage::DYNAMIC_DRAW: return GL_DYNAMIC_DRAW;
		default:
			DEVIAN_ASSERT_MSG(false, "UnKnown Usage!");
		}
	}
}

namespace DEVIAN {
	namespace GL {
		void GLVertexBuffer::Create() {
			glGenBuffers(1, &m_Handle);
			DEVIAN_ASSERT_MSG(m_Handle, "failed to create buffer!");
		}

		void GLVertexBuffer::Fill(const DEVIAN::BufferData& buffer, GLVertexBufferUsage usage = GLVertexBufferUsage::STATIC_DRAW) {
			glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
			glBufferData(GL_ARRAY_BUFFER, buffer.GetSize(), buffer.GetData(), ToGL(usage));
		}

		void GLVertexBuffer::Destroy() {
			glDeleteBuffers(1, &m_Handle);
		}
	}
}
