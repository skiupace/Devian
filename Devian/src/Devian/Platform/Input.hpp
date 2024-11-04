#pragma once
#include <Platform/Key.hpp>

namespace DEVIAN {
	class Input {
	public:
		bool IsKeyPressed(KeyCode);
		bool IsKeyReleased(KeyCode);
		bool IsMouseButtonPressed(MouseButton);
		bool IsMouseButtonReleased(MouseButton);
	};
}