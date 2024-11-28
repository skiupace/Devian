#pragma once
#include "Event.hpp"

#include <iostream>
#include <GLFW/glfw3.h>
#include <Core/Key.hpp>

namespace DEVIAN {
	class KeyEvent : public Event {
	public:
		KeyCode GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(const KeyCode keycode) : m_KeyCode(keycode) {}
		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(const KeyCode keyCode, bool isRepeat = false)
			: KeyEvent(keyCode), m_IsRepeat(isRepeat) {}

		static void OnApplicationKeyboardPressed(KeyCode keyCode) {
			try {
				printf("Key %s has been pressed!\n", glfwGetKeyName(static_cast<int>(keyCode), 0));
			} catch (std::exception ex) {
				std::cerr << ex.what() << std::flush;
			}
		}

	private:
		bool m_IsRepeat;
	};
}