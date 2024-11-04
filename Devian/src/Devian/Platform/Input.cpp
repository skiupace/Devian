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
}