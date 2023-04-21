#include "Rapier.h"

#include "Layer/Gui/EntityListPanel.h"

#include "imgui.h"

namespace Rapier {

	void EntityListPanel::SetScene(Ref<Scene> scene) {
		m_ActiveScene = scene;
	}


	void EntityListPanel::OnImGuiRender() {

		ImGui::Begin("EntityList");

		m_ActiveScene->m_Registry.each([&](auto entityId) {
			Entity entity{ entityId,m_ActiveScene.get()};

			auto& tag = entity.GetComponent<TagComponent>();
			ImGui::Text("%s", tag.Tag.c_str());
		});

		ImGui::End();

	}

}
