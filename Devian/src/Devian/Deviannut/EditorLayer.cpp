#include "EditorLayer.hpp"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace DEVIAN {
	void EditorLayer::ImGuiInit(void* NativeWindowHandle) {
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // IF using Docking Branch

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(NativeWindowHandle), true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init();

		glfwMakeContextCurrent(static_cast<GLFWwindow*>(NativeWindowHandle));
		glfwSwapInterval(1); // Enable V-Sync
	}

	void EditorLayer::InitFramebuffer() {
		// Create framebuffer
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		// Create texture to store the framebuffer content
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 565, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		// Create renderbuffer for depth and stencil
		glGenRenderbuffers(1, &depthStencil);
		glBindRenderbuffer(GL_RENDERBUFFER, depthStencil);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 565);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthStencil);

		// Check framebuffer completeness
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer is not complete!" << std::endl;

		// Unbind framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void EditorLayer::ResizeFramebuffer(int width, int height) {
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
		glBindRenderbuffer(GL_RENDERBUFFER, depthStencil);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	}

	void EditorLayer::SceneTab() {
		ImGui::Begin("Scene");
		
		// Bind framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glViewport(0, 0, 1280, 565); // Match framebuffer size
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Get elapsed time since program launch
		float time = static_cast<float>(glfwGetTime());

		// Vary color based on time
		float red = (std::sin(time * 0.5f) + 1.0f) / 2.0f;
		float green = (std::sin(time * 0.3f) + 1.0f) / 2.0f;
		float blue = (std::sin(time * 0.7f) + 1.0f) / 2.0f;

		// Set initial background color
		glClearColor(red, green, blue, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Unbind framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// Restore OpenGL viewport
		glViewport(0, 0, static_cast<GLsizei>(ImGui::GetIO().DisplaySize.x), static_cast<GLsizei>(ImGui::GetIO().DisplaySize.y));

		// Render the framebuffer texture inside the Scene tab
		ImGui::Image((void*)(intptr_t)texture, ImVec2(1280, 565), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
	}

	void EditorLayer::ObjectProperitiesTab() {
		static float f[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		ImGui::Begin("Properties");

		// Display sliders, throttle updates when possible
		ImGui::Text("Transformation Sliders:");
		if (ImGui::SliderFloat("x", &f[0], 0.0f, 1.0f)) { /* Update logic here */ }
		if (ImGui::SliderFloat("y", &f[1], 0.0f, 1.0f)) { /* Update logic here */ }
		if (ImGui::SliderFloat("z", &f[2], 0.0f, 1.0f)) { /* Update logic here */ }
		if (ImGui::SliderFloat("scale", &f[3], 0.0f, 1.0f)) { /* Update logic here */ }
		ImGui::ColorEdit3("", (float*)&clear_color);

		ImGui::End();
	}

	void EditorLayer::RenderUI() {
		if (!ImGui::GetCurrentContext()) {
			std::cerr << "ImGui context not initialized!" << std::endl;
			return;
		}

		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Create a dock space for layout
		static bool initialized = false; // To prevent resetting the layout every frame

		// Fullscreen dock space
		ImGuiWindowFlags dockspace_flags = ImGuiWindowFlags_NoDocking				|
			ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize					|
			ImGuiWindowFlags_NoMove		| ImGuiWindowFlags_NoBringToFrontOnFocus	|
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoNavFocus				| ImGuiWindowFlags_NoBackground;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f); // Remove window rounding
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f); // Remove window border
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f)); // Remove padding

		ImGui::Begin("DockSpace", nullptr, dockspace_flags);
		ImGui::PopStyleVar(3); // Pop all style changes

		// Create the dock space
		ImGuiID dockspace_id = ImGui::GetID("MainDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

		// Set up the layout (only once)
		if (!initialized) {
			ImGui::DockBuilderRemoveNode(dockspace_id); // Clear existing layout
			ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace); // Add central node

			ImGuiID dock_left = ImGui::DockBuilderSplitNode(dockspace_id, ImGuiDir_Left, 0.3f, nullptr, &dockspace_id);
			ImGuiID dock_main = dockspace_id; // Remaining space for the scene

			// Dock windows
			ImGui::DockBuilderDockWindow("Properties", dock_left);
			ImGui::DockBuilderDockWindow("Scene", dock_main);

			ImGui::DockBuilderFinish(dockspace_id);
			initialized = true;
		}

		ImGui::End();

		// Render your tabs
		ImGui::Begin("Properties");
		ObjectProperitiesTab(); // Your properties tab logic
		ImGui::End();

		ImGui::Begin("Scene");
		InitFramebuffer();
		SceneTab(); // Your scene tab logic
		ImGui::End();

		// Render ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	EditorLayer::~EditorLayer() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}