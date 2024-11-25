#include "GLVertexArray.hpp"

#include <glad/glad.h>
#include <Core/Core.hpp>

namespace {
	GLenum ToGL(DEVIAN::GL::GLShaderAttribType type) {
		switch (type) {
		case DEVIAN::GL::GLShaderAttribType::FLOAT: return GL_FLOAT;
		case DEVIAN::GL::GLShaderAttribType::INT: return GL_INT;
		default:
			DEVIAN_ASSERT_MSG(false, "Unknown Type!");
		}
	}
}

namespace DEVIAN {
	namespace GL {
		void GLVertexArray::Create() {
			glCreateVertexArrays(1, &m_Handle);
			DEVIAN_ASSERT_MSG(m_Handle, "failed to create vertexarray!");
		}

		void GLVertexArray::Destroy() {
			glDeleteVertexArrays(1, &m_Handle);
		}

		void GLVertexArray::AddIndexBuffer(GLIndexBuffer& indexbuffer) {
			glVertexArrayElementBuffer(m_Handle, indexbuffer.GetHandle());
		}

		void GLVertexArray::AddVertexBuffer(GLVertexBuffer& vertexbuffer, uint32_t stride) {
			glVertexArrayVertexBuffer(m_Handle, m_VertexBuffers.size(), vertexbuffer.GetHandle(), 0, stride);
			m_VertexBuffers.push_back(vertexbuffer);
		}

		void GLVertexArray::AddVertexAttrib(const GLVertexAttrib& attrib, uint32_t vertexbufferbindingindex = 0) {
			glVertexArrayAttribFormat(m_Handle, attrib.ShaderLocation, attrib.Count, ToGL(attrib.Type), false, attrib.Offset);
			glVertexArrayAttribBinding(m_Handle, attrib.ShaderLocation, vertexbufferbindingindex);

			glEnableVertexArrayAttrib(m_Handle, attrib.ShaderLocation);
		}

		void GLVertexArray::Bind() {
			glBindVertexArray(m_Handle);
		}
	}
}
