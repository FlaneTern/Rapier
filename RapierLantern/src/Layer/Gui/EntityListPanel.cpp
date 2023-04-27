#include "Rapier.h"

#include "Layer/Gui/EntityListPanel.h"

#include "imgui.h"

namespace Rapier {


	static Ref<Scene>  l_ActiveScene = nullptr;
	static bool l_NextFrame = true;
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
		ImGui::SetNextItemWidth(150);
		ImGui::SliderFloat(" Size", &cameraProjectionSize, 0.5f, 10.0f);
		ImGui::Unindent();
		ImGui::Dummy(ImVec2(0.0f, 20.0f));

		cameraComponent.Camera.SetSize(cameraProjectionSize);
	}

	static void DrawTransformComponentUI(Entity& entity) {
		auto& transform = entity.GetComponent<TransformComponent>();
		float* translate = (float*)&transform.Translation;
		float* rotation = (float*)&transform.Rotation;
		float* scale = (float*)&transform.Scale;

		ImGui::Text("Transform Component");
		ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
		ImGui::SetNextItemWidth(150);
		ImGui::SliderFloat3("Translation", translate, -5.0f, 5.0f);
		ImGui::SetNextItemWidth(150);
		ImGui::SliderFloat3("Rotation", rotation, 0.0f, 360.0f);
		ImGui::SetNextItemWidth(150);
		ImGui::SliderFloat3("Scale", scale, 0.0f, 5.0f);
		ImGui::Unindent();
		ImGui::Dummy(ImVec2(0.0f, 20.0f));

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

		static constexpr char addString[] = "Add Texture";
		static constexpr char reloadString[] = "Reload Texture";

		bool isWhiteTexture = spriteRendererComponent.Texture == AssetManager::GetWhiteTexture();
		if (ImGui::Button(isWhiteTexture ? addString : reloadString))
			ImGui::OpenPopup("Reload Texture");

		ImGui::SameLine();

		if(ImGui::Button("Remove Texture"))
			entity.ResetComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.8f, 0.8f, 1.0f });
		

		float* color = (float*)&spriteRendererComponent.Color;
		ImGui::SetNextItemWidth(150);
		ImGui::ColorEdit4("MyColor##2f", color);



		

		if (ImGui::BeginPopupModal("Reload Texture", NULL, ImGuiWindowFlags_MenuBar)) 
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
		const bool is_selected = l_ActiveScene->IsEntitySelected(entity);
		if (is_selected)
			node_flags |= ImGuiTreeNodeFlags_Selected;

		bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)(uint32_t)entity, node_flags, tag.Tag.c_str());

		// Currently Key Input gets blocked if main viewport is not focused
		// This breaks
		if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
			if (!Input::IsKeyPressed(RapierKey_LeftShift))
				l_ActiveScene->ClearSelectedEntities();
			l_ActiveScene->AddSelectedEntities(entity);
		}

		if (ImGui::BeginPopupContextItem()) {
			if (!Input::IsKeyPressed(RapierKey_LeftShift))
				l_ActiveScene->ClearSelectedEntities();
			l_ActiveScene->AddSelectedEntities(entity);

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
