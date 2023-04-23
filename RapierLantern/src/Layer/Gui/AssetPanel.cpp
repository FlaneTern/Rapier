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


		ImGui::Begin("Assets", (bool*)0, ImGuiWindowFlags_MenuBar);

        // Menu Bar
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
				if (ImGui::MenuItem("Refresh")) {
					FileSystem::RefreshTextureDirectory();
				}
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Examples"))
            {
				if (ImGui::MenuItem("halo")) RAPIER_CORE_INFO("halo");
                ImGui::EndMenu();
            }
			ImGui::EndMenuBar();
        }



		// Textures
		for (auto& entry : FileSystem::s_TextureDirectoryEntries) {
			ImGui::Text(entry.c_str());
			
			if (!FileSystem::IsDirectory(entry)) {
				Ref<Texture> texture = AssetManager::GetTexture2D(entry);
				if (texture)
					ImGui::ImageButton((void*)texture->GetRendererId(), ImVec2{ 128, 128 }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
				else
					ImGui::Text("Texture not loaded");
			}

		}

		ImGui::End();
	}

}