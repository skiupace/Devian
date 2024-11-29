#include "Application.hpp"

#include <iostream>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

#include <Core/Core.hpp>
#include <Platform/WindowsPlatform.hpp>

#include <Platform/GL/GLCommands.hpp>
#include <Platform/GL/GLGraphicsContext.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace DEVIAN {
	Application::Application(const ApplicationSpecs& specs) : m_AppSpecs(specs) {
		#if defined(_WIN32) || defined(_WIN64)
			m_Instance = this;
			m_Platform = std::make_unique<WindowsPlatformLayer>();
			m_Platform->CreateNativeWindow(specs.width, specs.height, specs.title.c_str());
		#else
			#error This Engine is Currently Supports Windows Platform Only!
		#endif

		switch (specs.api) {
		case OPENGL:
			m_GraphicsContext = std::make_unique<GL::GLGraphicsContext>();
			m_GraphicsContext->Init(m_Platform->GetNativeWindowHandle());
			break;

		case VULKAN:
			DEVIAN_ASSERT_MSG(false, "Vulkan Not Supported Yet!");
			break;

		case NONE:
			DEVIAN_ASSERT_MSG(false, "Failed to specify garphics API");
		}

		// Camera Setup
		m_Camera = Camera3D(glm::vec3(0.0f, 0.0f, 5.0f));

		std::vector<glm::vec3> vertices = {
			{ 0.5f,  0.5f, 0.0f },  // top right
			{ 0.5f, -0.5f, 0.0f },  // bottom right
			{-0.5f, -0.5f, 0.0f },  // bottom left
			{-0.5f,  0.5f, 0.0f }	// top left
		};

		std::vector<uint32_t> indices = {
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};

		// VBO
		GL::GLVertexBuffer QuadVertexBuffer;
		QuadVertexBuffer.Create();
		QuadVertexBuffer.Fill(BufferData::CreateFrom(vertices), GL::GLVertexBufferUsage::STATIC_DRAW);

		// EBO
		GL::GLIndexBuffer QuadIndexBuffer;
		QuadIndexBuffer.Create();
		QuadIndexBuffer.Fill(indices);

		// VAO
		QuadVertexArray.Create();
		QuadVertexArray.AddVertexBuffer(QuadVertexBuffer, sizeof(glm::vec3));
		QuadVertexArray.AddIndexBuffer(QuadIndexBuffer);

		{
			GL::GLVertexAttrib PositionAttrib;
			PositionAttrib.ShaderLocation = 0;
			PositionAttrib.Count = 3;
			PositionAttrib.Type = GL::GLShaderAttribType::FLOAT;
			PositionAttrib.Offset = 0;

			QuadVertexArray.AddVertexAttrib(PositionAttrib);
		}

		Shader.LoadFromFile("res/gl shaders/pos_vertex.vert", "res/gl shaders/pos_fragment.frag");

		CameraUnifromBuffer.Create(0);
	}

	inline bool Application::IsRunning() noexcept {
		return !glfwWindowShouldClose(static_cast<GLFWwindow*>(m_Platform->GetNativeWindowHandle()));
	}

	void Application::Run() {
		try {
			while (IsRunning()) {
				{ // Calculate DeltaTime
					float CurrentFrame = static_cast<float>(glfwGetTime());
					m_DeltaTime = CurrentFrame - m_LastTime;
					m_LastTime = CurrentFrame;
				}

				// Poll Events
				m_Platform->PollEvents();

				m_Camera.Update(m_DeltaTime);

				// Graphics
				GL::GLCommands::Clear(0.1f, 0.1f, 0.1f, 1.0f);
				GL::GLCommands::ClearFlag(GL::ClearFlags::COLOR);
				Shader.Bind();

				{
					glm::mat4 proj = m_Camera.GetProjectionMatrix() * m_Camera.GetViewMatrix();

					BufferData CameraBuffer = { &proj, sizeof(glm::mat4) };
					CameraUnifromBuffer.Update(CameraBuffer);

					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))
						* glm::rotate(glm::mat4(1.0f), static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 1.0f, 0.0f));

					Shader.SetMat4("model", model);
				}

				QuadVertexArray.Bind();
				GL::GLCommands::DrawIndexed(GL::Primitive::TRIANGLES, 6);

				m_GraphicsContext->SwapBuffers(m_Platform->GetNativeWindowHandle());

				Input::ResetInput();
			}
		} catch (const std::exception& ex) {
			spdlog::error(ex.what());
			return;
		}
	}

	Application& Application::Get() {
		return *m_Instance;
	}

	PlatformLayer* Application::GetPlatformLayer() {
		return m_Platform.get();
	}

	ApplicationSpecs Application::GetApplicationSpecs() {
		return m_AppSpecs;
	}

	void Application::SetWidth(uint32_t width) {
		m_AppSpecs.width = width;
	}

	void Application::SetHeight(uint32_t height) {
		m_AppSpecs.width = height;
	}

	void Application::SetWindowSizeCallBack(const WindowSizeCallBackFuncPtr& func) {
		m_WindowSizeCallBackFuncPtr = func;
	}

	void Application::SetKeyboardCallBack(const KeyboardCallBackFuncPtr& func) {
		m_KeyboardCallBackFuncPtr = func;
	}

	WindowSizeCallBackFuncPtr Application::GetWindowSizeCallBack() {
		return m_WindowSizeCallBackFuncPtr;
	}

	KeyboardCallBackFuncPtr Application::GetKeyboardCallBack() {
		return m_KeyboardCallBackFuncPtr;
	}

	Application::~Application() {
		m_Instance = nullptr;
		m_Platform = nullptr;
	}
}