#include "Rapier.h"

#include "Layer/Gui/AssetPanel.h"
#include "FileSystem/FileSystem.h"

#include "Renderer/Framebuffer.h"

#include "imgui.h"

namespace Rapier {


	void AssetPanel::OnImGuiRender() {

		DrawTexturePanel();
		DrawShaderPanel();

	}

	void AssetPanel::DrawTexturePanel() {

		ImGui::Begin("Textures", (bool*)0, ImGuiWindowFlags_MenuBar);

		// Menu Bar
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Refresh")) {
					FileSystem::RefreshTextureDirectory();
					AssetManager::LoadAllTexture2Ds();
				}
				if (ImGui::MenuItem("Delete textures")) {
					AssetManager::UnloadAllTexture2Ds();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Examples"))
			{
				if (ImGui::MenuItem("halo"))
					RAPIER_CORE_INFO("halo");
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}


		uint32_t samelineCount = ImGui::GetContentRegionAvail().x / 150;
		samelineCount = std::max(samelineCount, (uint32_t)1);
		uint32_t count = 0;


		ImGui::PushItemWidth(150);
		for (auto& entry : FileSystem::s_TextureDirectoryEntries) {

			ImGui::BeginGroup();

			Ref<Texture> texture = AssetManager::GetTexture2D(entry);
			if (texture) {
				ImGui::ImageButton((void*)texture->GetRendererId(), ImVec2{ 128, 128 }, ImVec2{ 0,1 }, ImVec2{ 1,0 });

				if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
				{
					const char* textureName = texture->GetFilepath().c_str();
					ImGui::SetDragDropPayload("TextureDND", textureName, texture->GetFilepath().length() + 1);

					// Display preview (could be anything, e.g. when dragging an image we could decide to display
					// the filename and a small preview of the image, etc.)
					ImGui::Text(entry.c_str());
					ImGui::EndDragDropSource();
				}
			}
			else {
				ImGui::Text("Texture not loaded!");
			}

			ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 150);
			ImGui::Text(entry.c_str());
			ImGui::PopTextWrapPos();

			ImGui::EndGroup();
			count++;

			if (count % samelineCount == 0)
				count = 0;
			else
				ImGui::SameLine();
		}
		ImGui::PopItemWidth();


		ImGui::End();
	}

	void AssetPanel::DrawShaderPanel() {
		ImGui::Begin("Shaders", (bool*)0, ImGuiWindowFlags_MenuBar);

		// Menu Bar
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("kekl"))
			{
				if (ImGui::MenuItem("kek"))
					RAPIER_CORE_INFO("kek");
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}


		for (auto& entry : FileSystem::s_ShaderDirectoryEntries) {
			ImGui::Text(entry.c_str());
		}


		ImGui::End();
	}
}