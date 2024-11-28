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

        //[[maybe_unused]] //! Require C++17.
        //auto finally = std::unique_ptr<void, std::function<void(void*)>>(nullptr, [&app](void*) {
        //    app = nullptr;
        //});
    } catch (std::exception ex) {
        std::cerr << ex.what() << std::flush;
        return -1;
    }

	return EXIT_SUCCESS;
}