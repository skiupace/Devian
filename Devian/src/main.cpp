#include <iostream>
#include <Platform/Key.hpp>
#include <Core/Application.hpp>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

static void OnApplicationResize(GLFWwindow* window, int width, int height) {
    std::cout << "Width: " << width << ", Height: " << height << '\n';
}

static void OnApplicationKeyboardPressed(GLFWwindow* window, int keyCode, int scanCode, int action, int mods) {
    if (static_cast<DEVIAN::KeyCode>(keyCode) == DEVIAN::KeyCode::F)
        std::cout << "F Key has been pressed!\n";
    //std::cout << "Key " << glfwGetKeyName(keyCode, scanCode) << " has been pressed!\n";
}

int main(int argc, char** argv) {

    mono_set_assemblies_path("vendor/mono/lib");
    auto domain = mono_jit_init("DevianScriptingEngine");

    if (domain) {
        auto assembly = mono_domain_assembly_open(domain, "Resources\\Release\\net8.0\\TestGame.dll");
        if (assembly) {
            auto image = mono_assembly_get_image(assembly);

            MonoClass* TestScript = mono_class_from_name(image, "TestGame", "TestScript");

            // Create Object
            MonoObject* my_class_instance = mono_object_new(domain, TestScript);

            // Call Constructor
            mono_runtime_object_init(my_class_instance);

            // Calling Start Method
            MonoMethod* start_method = mono_class_get_method_from_name(TestScript, "Start", 0);
            mono_runtime_invoke(start_method, my_class_instance, nullptr, nullptr);

            // Calling Update Method
            MonoMethod* update_method = mono_class_get_method_from_name(TestScript, "Update", 0);
            mono_runtime_invoke(update_method, my_class_instance, nullptr, nullptr);
        }
    }

    #if false
    try {
        DEVIAN::ApplicationSpecs specs;
        specs.width = 900;
        specs.height = 600;
        specs.title = "Devian Engine";

        DEVIAN::Application* App = new DEVIAN::Application(specs);
        App->SetWindowSizeCallBack(OnApplicationResize);
        App->SetKeyboardCallBack(OnApplicationKeyboardPressed);

        App->Run();
        delete App;
}
    catch (std::exception ex) {
        std::cerr << ex.what() << std::flush;
        return EXIT_FAILURE;
    }
    #endif

	std::cin.get();
	return EXIT_SUCCESS;
}