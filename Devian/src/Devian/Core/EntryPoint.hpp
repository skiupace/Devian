#pragma once
#include <memory>
#include <functional>

extern DEVIAN::Application* DEVIAN::CreateApplication();

int main(int argc, char** argv) {

    try {
        auto app = DEVIAN::CreateApplication();
        app->ExecuteScript();

        app->SetWindowSizeCallBack(DEVIAN::WindowResizeEvent::OnApplicationResize);
        app->SetKeyboardCallBack(DEVIAN::KeyPressedEvent::OnApplicationKeyboardPressed);
        app->Run();
    } catch (const std::exception& ex) {
        spdlog::error(ex.what());
        return EXIT_FAILURE;
    }

	return EXIT_SUCCESS;
}