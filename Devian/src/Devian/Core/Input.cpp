#include "Input.hpp"
#include <Core/Application.hpp>

namespace DEVIAN {
	bool Input::IsKeyPressed(KeyCode keyCode) {
		return Application::Get().GetPlatformLayer()->IsKeyPressed(static_cast<int>(keyCode));
	}

	bool Input::IsKeyReleased(KeyCode keyCode) {
		return Application::Get().GetPlatformLayer()->IsKeyReleased(static_cast<int>(keyCode));
	}

	bool Input::IsMouseButtonPressed(MouseButton mouseButton) {
		return Application::Get().GetPlatformLayer()->IsMouseButtonPressed(static_cast<int>(mouseButton));
	}

	bool Input::IsMouseButtonReleased(MouseButton mouseButton) {
		return Application::Get().GetPlatformLayer()->IsMouseButtonReleased(static_cast<int>(mouseButton));
	}

	void Input::SetMousePosition(const glm::vec2& value) { MousePosition = value; }
	glm::vec2 Input::GetMousePosition() { return MousePosition; }

	void Input::SetMouseOffset(const glm::vec2& value) { MouseOffset = value; }
	glm::vec2 Input::GetMouseOffset() { return MouseOffset; }

	void Input::SetMouseScroll(const glm::vec2& value) { MouseScroll = value; }
	glm::vec2 Input::GetMouseScroll() { return MouseScroll; }

	void Input::ResetInput() {
		MouseOffset = { 0.0f, 0.0f };
		MouseScroll = { 0.0f, 0.0f };
	}
}