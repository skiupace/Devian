#pragma once
#include "Event.hpp"
#include <iostream>

namespace DEVIAN {
	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent() = default;
		static void OnApplicationResize(unsigned int width, unsigned int height) {
			spdlog::info("Width: {}, Height : {}", width, height);
		}
	};
}