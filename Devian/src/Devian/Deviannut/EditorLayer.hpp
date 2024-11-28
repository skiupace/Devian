#pragma once
#include <Core/Application.hpp>

namespace DEVIAN {
	class EditorLayer {
	public:
		EditorLayer() = default;
		~EditorLayer();

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