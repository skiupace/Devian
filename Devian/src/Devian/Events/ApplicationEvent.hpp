#pragma once
#include "Event.hpp"
#include <iostream>

namespace DEVIAN {
	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent() = default;
		static void OnApplicationResize(unsigned int width, unsigned int height) {
			std::cout << "Width: " << width << ", Height: " << height << '\n';
		}
	};
}