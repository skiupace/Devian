#pragma once
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

namespace DEVIAN {
	class ScriptingEngine {
	public:
		ScriptingEngine() = default;
		ScriptingEngine(const char*);
		void ExecuteScript();

	private:
		MonoDomain* domain;
		MonoAssembly* assembly;
		MonoImage* image;
	};
}