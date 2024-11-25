#pragma once
#include <stdint.h>

namespace DEVIAN {
	namespace GL {
		enum class ClearFlags { COLOR, DEPTH, COLOR_DEPTH };
		enum class Primitive { LINE_LOOP, TRIANGLES };

		class GLCommands {
		public:
			static void Clear(float, float, float, float);
			static void ClearFlag(ClearFlags);
			static void SetViewPort(uint32_t, uint32_t);
			static void DrawArrays(Primitive, uint32_t);
			static void DrawIndexed(Primitive, uint32_t);
		};
	}
}
