#include "Rapier.h"

#include "Layer/Gui/AssetPanel.h"
#include "FileSystem/FileSystem.h"

#include "Renderer/Framebuffer.h"

#include "imgui.h"

namespace Rapier {


	static Ref<Scene>  l_ActiveScene = nullptr;
	static bool l_NextFrame = true;
	static int l_id = 0;
	static uint32_t l_Selected = -1;
	static char l_Newname[64] = "";


	void AssetPanel::OnImGuiRender() {
		l_ActiveScene = m_ActiveScene;

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
			if (texture)
				ImGui::ImageButton((void*)texture->GetRendererId(), ImVec2{ 128, 128 }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
			else
				ImGui::Text("Texture not loaded!");

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