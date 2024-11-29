#include "GLCommands.hpp"

#include <glad/glad.h>
#include <Core/Core.hpp>

namespace DEVIAN {
	GLuint ToGL(GL::ClearFlags flag) {
		switch (flag) {
		case GL::ClearFlags::COLOR: return GL_COLOR_BUFFER_BIT;
		case GL::ClearFlags::DEPTH: return GL_DEPTH_BUFFER_BIT;
		case GL::ClearFlags::COLOR_DEPTH: return GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
		default:
			DEVIAN_ASSERT_MSG(false, "UnKnown flag!");
		}
	}

	GLenum ToGL(GL::Primitive primitive) {
		switch (primitive) {
		case GL::Primitive::LINE_LOOP: return GL_LINE_LOOP;
		case GL::Primitive::TRIANGLES: return GL_TRIANGLES;
		default:
			DEVIAN_ASSERT_MSG(false, "UnKnown primitive!");
		}
	}
}


namespace DEVIAN {
	namespace GL {
		void GLCommands::Clear(float r, float g, float b, float a) {
			glClearColor(r, g, b, a);
		}

		void GLCommands::ClearFlag(ClearFlags flag) {
			glClear(ToGL(flag));
		}

		void GLCommands::SetViewPort(uint32_t width, uint32_t height) {
			glViewport(0, 0, width, height);
		}

		void GLCommands::DrawArrays(Primitive primitive, uint32_t count) {
			glDrawArrays(ToGL(primitive), 0, count);
		}

		void GLCommands::DrawIndexed(Primitive primitive, uint32_t count) {
			glDrawElements(ToGL(primitive), count, GL_UNSIGNED_INT, nullptr);
		}
	}
}
