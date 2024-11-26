#include <memory>
#include <iostream>
#include <functional>
#include <GLFW/glfw3.h>
#include <Core/Key.hpp>
#include <UI/DevianUI.hpp>
#include <Scripting/Script.hpp>
#include <Core/Application.hpp>

static void OnApplicationResize(int width, int height) {
    std::cout << "Width: " << width << ", Height: " << height << '\n';
}

static void OnApplicationKeyboardPressed(DEVIAN::KeyCode keyCode) {
    try {
        printf("Key %s has been pressed!\n", glfwGetKeyName(static_cast<int>(keyCode), 0));
    } catch (std::exception ex) {
        std::cerr << ex.what() << std::flush;
    }
}

int main(int argc, char** argv) {

    #if true
    std::unique_ptr<DEVIAN::ScriptingEngine> testScript = std::make_unique<DEVIAN::ScriptingEngine>(
        R"(C:\Dev\Projects\C++ Projects\Game Engine\Devian\Devian\Resources\Release\net8.0\TestGame.dll)"
    );

    testScript->ExecuteScript();
    #endif

    #if true
    try {
        DEVIAN::ApplicationSpecs specs = {
            .width = 900,
            .height = 600,
            .title = "Devian Engine"
        };

        std::unique_ptr<DEVIAN::Application> app = std::make_unique<DEVIAN::Application>(specs);
        app->SetWindowSizeCallBack(OnApplicationResize);
        app->SetKeyboardCallBack(OnApplicationKeyboardPressed); 
        app->Run();

        [[maybe_unused]] //! Require C++17.
        auto finally = std::unique_ptr<void, std::function<void(void*)>>(nullptr, [&app](void*) {
            app = nullptr;
        });
    } catch (std::exception ex) {
        std::cerr << ex.what() << std::flush;
        return EXIT_FAILURE;
    }
    #endif

	return EXIT_SUCCESS;
}