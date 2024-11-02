#pragma once

namespace DEVIAN {
	class DevianUI {
	public:
		DevianUI() = default;
		~DevianUI();

		void ImGuiInit(void*);
		void RenderUI();
	};
}