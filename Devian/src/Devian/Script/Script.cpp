#include "Script.hpp"

namespace DEVIAN {
    ScriptingEngine::ScriptingEngine(const char* path) {
        mono_set_assemblies_path(R"(C:\Dev\Projects\C++ Projects\Game Engine\Devian\Devian\vendor\mono\lib)");
        domain = mono_jit_init("DevianScriptingEngine");

        assembly = mono_domain_assembly_open(domain, path);
        image = mono_assembly_get_image(assembly);
    }

	void ScriptingEngine::ExecuteScript() {
        if (domain) {
            if (assembly) {
                MonoClass* TestScript = mono_class_from_name(image, "TestGame", "TestScript");

                // Create Object
                MonoObject* myClassInstance = mono_object_new(domain, TestScript);

                // Call Constructor
                mono_runtime_object_init(myClassInstance);

                // Calling Start Method
                MonoMethod* startMethod = mono_class_get_method_from_name(TestScript, "Start", 0);
                mono_runtime_invoke(startMethod, myClassInstance, nullptr, nullptr);

                // Calling Update Method
                MonoMethod* updateMethod = mono_class_get_method_from_name(TestScript, "Update", 0);
                mono_runtime_invoke(updateMethod, myClassInstance, nullptr, nullptr);
            }
        }
	}
}