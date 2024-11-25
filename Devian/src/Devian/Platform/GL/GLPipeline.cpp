#include "GLPipeline.hpp"
#include <glad/glad.h>

namespace DEVIAN {
	namespace GL {
		void GLPipeline::EnableMultiSample() {
			glEnable(GL_MULTISAMPLE);
		}
	}
}
