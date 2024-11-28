#include <Devian.hpp>

class Sandbox : public DEVIAN::Application {
public:
	Sandbox() {
		m_Specs = {
			.width = 900,
			.height = 600,
			.title = "Devian Engine"
		};

		m_App = std::make_unique<DEVIAN::Application>(m_Specs);

		m_TestScript = std::make_unique<DEVIAN::ScriptingEngine>(
			R"(C:\Dev\Projects\C++ Projects\Game Engine\Devian\Devian\Resources\Release\net8.0\TestGame.dll)"
		);
	}

	void SetWindowSizeCallBack(const DEVIAN::WindowSizeCallBackFuncPtr& func) override {
		m_App->SetWindowSizeCallBack(func);
	}

	void SetKeyboardCallBack(const DEVIAN::KeyboardCallBackFuncPtr& func) override {
		m_App->SetKeyboardCallBack(func);
	}

	void Run() override {
		m_App->Run();
	}

	void ExecuteScript() override {
		m_TestScript->ExecuteScript();
	}

	~Sandbox() {
		m_TestScript = nullptr;
	}

private:
	DEVIAN::ApplicationSpecs m_Specs;
	std::unique_ptr<DEVIAN::Application> m_App;
	std::unique_ptr<DEVIAN::ScriptingEngine> m_TestScript;
	std::unique_ptr<DEVIAN::KeyPressedEvent> m_KeyPressedEvent;
	std::unique_ptr<DEVIAN::WindowResizeEvent> m_WindowResizeEvent;
};

DEVIAN::Application* DEVIAN::CreateApplication() {
	return new Sandbox();
}