#pragma once
#include <glm/glm.hpp>
#include <Core/Key.hpp>

namespace DEVIAN {
	class Input {
	public:
		static bool IsKeyPressed(KeyCode);
		static bool IsKeyReleased(KeyCode);

		static bool IsMouseButtonPressed(MouseButton);
		static bool IsMouseButtonReleased(MouseButton);

		static void SetMousePosition(const glm::vec2&);
		static glm::vec2 GetMousePosition();

		static void SetMouseOffset(const glm::vec2&);
		static glm::vec2 GetMouseOffset();

		static void SetMouseScroll(const glm::vec2&);
		static glm::vec2 GetMouseScroll();

		static void ResetInput();

	private:
		inline static glm::vec2 MousePosition;
		inline static glm::vec2 MouseOffset;
		inline static glm::vec2 MouseScroll;
	};
}