#include <iostream>
#include <Platform/Key.hpp>
#include <Script/Script.hpp>
#include <Core/Application.hpp>

static void OnApplicationResize(GLFWwindow* window, int width, int height) {
    std::cout << "Width: " << width << ", Height: " << height << '\n';
}

static void OnApplicationKeyboardPressed(GLFWwindow* window, int keyCode, int scanCode, int action, int mods) {
    if (static_cast<DEVIAN::KeyCode>(keyCode) == DEVIAN::KeyCode::F)
        std::cout << "F Key has been pressed!\n";
    //std::cout << "Key " << glfwGetKeyName(keyCode, scanCode) << " has been pressed!\n";
}

int main(int argc, char** argv) {

    #if true
    std::unique_ptr<DEVIAN::ScriptingEngine> testScript = std::make_unique<DEVIAN::ScriptingEngine>(R"(C:\Dev\Projects\C++ Projects\Game Engine\Devian\Devian\Resources\Release\net8.0\TestGame.dll)");
    testScript->ExecuteScript();
    #endif

    #if true
    try {
        DEVIAN::ApplicationSpecs specs = {
            .width = 900,
            .height = 600,
            .title = "Devian Engine"
        };

        std::unique_ptr<DEVIAN::Application> App = std::make_unique<DEVIAN::Application>(specs);
        App->SetWindowSizeCallBack(OnApplicationResize);
        App->SetKeyboardCallBack(OnApplicationKeyboardPressed);
        App->Run();
    } catch (std::exception ex) {
        std::cerr << ex.what() << std::flush;
        return EXIT_FAILURE;
    }
    #endif

	std::cin.get();
	return EXIT_SUCCESS;
}