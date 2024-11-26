#pragma once
#include <Core/Application.hpp>

namespace DEVIAN {
	class DevianUI {
	public:
		DevianUI() = default;
		~DevianUI();

		void ImGuiInit(void*);
		void RenderUI();

		void InitFramebuffer();
		void ResizeFramebuffer(int, int);

	private:
		void SceneTab();
		void ObjectProperitiesTab();

	private:
		// Framebuffer objects
		unsigned int framebuffer;
		unsigned int texture;
		unsigned int depthStencil;
	};
}