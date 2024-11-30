#include "GLVertexArray.hpp"

#include <glad/glad.h>
#include <Core/Core.hpp>

namespace DEVIAN {
	GLenum ToGL(GL::GLShaderAttribType type) {
		switch (type) {
		case GL::GLShaderAttribType::FLOAT: return GL_FLOAT;
		case GL::GLShaderAttribType::INT: return GL_INT;
		default:
			DEVIAN_ASSERT_MSG(false, "Unknown Type!");
		}
	}
}

namespace DEVIAN {
	namespace GL {
		void GLVertexArray::Create() {
			glCreateVertexArrays(1, &m_Handle);
			DEVIAN_ASSERT_MSG(m_Handle, "failed to create vertex array!");
		}

		void GLVertexArray::Destroy() {
			glDeleteVertexArrays(1, &m_Handle);
		}

		void GLVertexArray::AddIndexBuffer(GLIndexBuffer& indexBuffer) {
			glVertexArrayElementBuffer(m_Handle, indexBuffer.GetHandle());
		}

		void GLVertexArray::AddVertexBuffer(GLVertexBuffer& vertexBuffer, uint32_t stride) {
			glVertexArrayVertexBuffer(m_Handle, static_cast<GLsizei>(m_VertexBuffers.size()), vertexBuffer.GetHandle(), 0, stride);
			m_VertexBuffers.push_back(vertexBuffer);
		}

		void GLVertexArray::AddVertexAttrib(const GLVertexAttrib& attrib, uint32_t vertexBufferBindingIndex) {
			glVertexArrayAttribFormat(m_Handle, attrib.ShaderLocation, attrib.Count, ToGL(attrib.Type), false, attrib.Offset);
			glVertexArrayAttribBinding(m_Handle, attrib.ShaderLocation, vertexBufferBindingIndex);

			glEnableVertexArrayAttrib(m_Handle, attrib.ShaderLocation);
		}

		void GLVertexArray::Bind() {
			glBindVertexArray(m_Handle);
		}
	}
}
