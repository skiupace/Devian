#include <iostream>
#include <Platform/Key.hpp>
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

    DEVIAN::ApplicationSpecs specs;
    specs.width = 900;
    specs.height = 600;
    specs.title = "Devian Engine";

    DEVIAN::Application* App = new DEVIAN::Application(specs);
    App->SetWindowSizeCallBack(OnApplicationResize);
    App->SetKeyboardCallBack(OnApplicationKeyboardPressed);

    App->Run();
    delete App;

	std::cin.get();
	return EXIT_SUCCESS;
}