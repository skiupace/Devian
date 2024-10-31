#include <iostream>
#include <Core/Application.hpp>

int main(int argc, char** argv) {

    DEVIAN::ApplicationSpecs specs;
    specs.width = 900;
    specs.height = 600;
    specs.title = "Devian Engine";

    DEVIAN::Application* App = new DEVIAN::Application(specs);
    App->Run();
    delete App;

	std::cin.get();
	return EXIT_SUCCESS;
}