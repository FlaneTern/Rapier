#pragma once

#include "Layer/Gui/Panel.h"

namespace Rapier {

	class EntityListPanel : public Panel {
	public:
		EntityListPanel(Ref<Scene> scene)
			: Panel(scene) {}

		virtual void OnImGuiRender() override;
	};
}