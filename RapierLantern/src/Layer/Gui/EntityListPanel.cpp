#include "Rapier.h"

#include "Layer/Gui/EntityListPanel.h"

#include "imgui.h"

namespace Rapier {


	static Ref<Scene>  l_ActiveScene = nullptr;
	static bool l_NextFrame = true;
	static uint32_t l_Selected = -1;
	static char l_Newname[64] = "";


	static void DrawCameraComponentUI(Entity& entity) {
		// Camera projection
		auto& cameraComponent = entity.GetComponent<CameraComponent>();
		float cameraProjectionSize = cameraComponent.Camera.GetSize();

		ImGui::Text("Camera Component");
		ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
		if (cameraComponent.Primary) {
			ImGui::Text("Primary Camera");
		}
		else if (ImGui::Button("Set as Primary Camera")) {
			l_ActiveScene->SetPrimaryCamera(entity);
		}
		ImGui::SliderFloat(" Size", &cameraProjectionSize, 0.0f, 10.0f);
		ImGui::Unindent();
		ImGui::Dummy(ImVec2(0.0f, 20.0f));

		cameraComponent.Camera.SetSize(cameraProjectionSize);
	}

	static void DrawTransformComponentUI(Entity& entity) {
		auto& transform = entity.GetComponent<TransformComponent>().Transform;
		float translate[] = { transform[3][0], transform[3][1], transform[3][2] };

		ImGui::Text("Transform Component");
		ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
		ImGui::SliderFloat3("Position", translate, -5.0f, 5.0f);
		ImGui::Unindent();
		ImGui::Dummy(ImVec2(0.0f, 20.0f));

		transform[3][0] = translate[0];
		transform[3][1] = translate[1];
		transform[3][2] = translate[2];
	}

	static void DrawNativeScriptComponentUI(Entity& entity) {
		auto& nativeScriptComponent = entity.GetComponent<NativeScriptComponent>();

		ImGui::Text("Native Script Component");
		ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
		ImGui::Checkbox("Script Enable OnUpdate", &nativeScriptComponent.Instance->EnableOnUpdate);
		ImGui::Unindent();
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
	}

	static void DrawSpriteRendererComponentUI(Entity& entity) {
		auto& spriteRendererComponent = entity.GetComponent<SpriteRendererComponent>();

		ImGui::Text("Sprite Renderer Component");
		ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
		if (spriteRendererComponent.Texture) {
			if (ImGui::Button("Reload Texture"))
				ImGui::OpenPopup("Reload Texture");

			if(ImGui::Button("Remove Texture"))
				entity.ResetComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.8f, 0.8f, 1.0f });
		}
		else {
			float* color = (float*)&spriteRendererComponent.Color;
			ImGui::ColorEdit4("MyColor##2f", color);

			if (ImGui::Button("Add Texture"))
				ImGui::OpenPopup("Add Texture");

		}

		if (ImGui::BeginPopupModal("Reload Texture", NULL, ImGuiWindowFlags_MenuBar)
			|| ImGui::BeginPopupModal("Add Texture", NULL, ImGuiWindowFlags_MenuBar)) 
		{
			for (const auto& textureRef : AssetManager::GetAllTexture2D()) {
				if (ImGui::Button(textureRef->GetFilepath().c_str())) {
					entity.ResetComponent<SpriteRendererComponent>(textureRef);
					ImGui::CloseCurrentPopup();
				}
			}

			if (ImGui::Button("Cancel")) {
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		ImGui::Unindent();
		ImGui::Dummy(ImVec2(0.0f, 20.0f));
	}





	template<typename... Args>
	static bool DrawAddRemoveAllComponents(Entity& entity) {
		bool modified = false;

		([&] {
			bool hasComponent = entity.HasComponent<Args>();
			if (hasComponent && ImGui::Button(Args::RemoveName.data())) {
				entity.RemoveComponent<Args>();
				modified = true;
			}

			if (!hasComponent && ImGui::Button(Args::AddName.data())) {
				entity.AddComponent<Args>();
				modified = true;
			}

		}(), ...);

		return modified;
	}


	// Combine with other components ? ////////////////////
	// Implement script chooser
	static bool DrawAddRemoveNativeScriptComponentPopup(Entity& entity) {
		bool hasComponent = entity.HasComponent<NativeScriptComponent>();
		if (hasComponent && ImGui::Button(NativeScriptComponent::RemoveName.data())) {
			entity.RemoveComponent<NativeScriptComponent>();
			return true;
		}

		if (!hasComponent && ImGui::Button(NativeScriptComponent::AddName.data())) {
			auto& script = entity.AddComponent<NativeScriptComponent>();
			script.Bind<EntityScript>(); script.Instance = script.InstantiateScript();
			return true;
		}

		return false;
	}






	static void DrawEntityUI(entt::entity entityId) {

		bool destroy = false;

		Entity entity{ entityId, l_ActiveScene.get() };
		auto& tag = entity.GetComponent<TagComponent>();


		static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;


		ImGuiTreeNodeFlags node_flags = base_flags;
		const bool is_selected = l_Selected == (uint32_t)entity;
		if (is_selected)
			node_flags |= ImGuiTreeNodeFlags_Selected;

		bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)(uint32_t)entityId, node_flags, tag.Tag.c_str());

		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
			l_Selected = entity;

		if (ImGui::BeginPopupContextItem()) {
			l_Selected = entity;

			bool renamed = false;

			bool modifiedComponent = false;

			if (ImGui::Button("Add/Remove Components"))
				ImGui::OpenPopup("Add/Remove Components");

			if (ImGui::BeginPopup("Add/Remove Components")) {

				modifiedComponent |= DrawAddRemoveAllComponents<COMPONENTS_LIST>(entity);
				modifiedComponent |= DrawAddRemoveNativeScriptComponentPopup(entity);

				ImGui::EndPopup();
			}


			if (ImGui::Button("Rename Entity")) 
				ImGui::OpenPopup("Rename Entity");
				
			if (ImGui::BeginPopup("Rename Entity")) {
				ImGui::InputText("Rename Entity", l_Newname, sizeof(l_Newname));

				if (ImGui::Button("Ok")) {
					entity.GetComponent<TagComponent>().Tag = l_Newname;
					strcpy(l_Newname, "\0");
					renamed = true;
					ImGui::CloseCurrentPopup();
				}

				if (ImGui::Button("Cancel")) {
					strcpy(l_Newname, "\0");
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			if (ImGui::Button("Delete Entity")) {
				destroy = true;
				ImGui::CloseCurrentPopup();
			}

			if(renamed || modifiedComponent)
				ImGui::CloseCurrentPopup();

			ImGui::EndPopup();
		}

		if (node_open) {
			ImGui::Separator();
			if (entity.HasComponent<TransformComponent>()) 
				DrawTransformComponentUI(entity);
			if (entity.HasComponent<CameraComponent>()) 
				DrawCameraComponentUI(entity);
			if (entity.HasComponent<SpriteRendererComponent>()) 
				DrawSpriteRendererComponentUI(entity);
			if (entity.HasComponent<NativeScriptComponent>()) 
				DrawNativeScriptComponentUI(entity);

			ImGui::TreePop();
		}

		ImGui::Separator();

		if (destroy) {
			l_ActiveScene->DestroyEntity(entity);
		}

	}



	void EntityListPanel::OnImGuiRender() {

		l_ActiveScene = m_ActiveScene;
		ImGui::Begin("EntityList");


		if (ImGui::Button("Add Entity")) {
			Entity entity = m_ActiveScene->CreateEntity();
			entity.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.8f, 0.8f, 1.0f });
		}
		ImGui::Separator();

		m_ActiveScene->m_Registry.each(DrawEntityUI);
		static bool p_open = true;
		ImGui::ShowDemoWindow(&p_open);

		ImGui::End();

	}

}
