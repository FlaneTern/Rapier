#include "Layer/LanternLayer.h"
#include "RapierLantern.h"
#include "Serializer/SceneSerializer.h"
#include "Assets/Script/Script.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"



namespace Rapier {

	void LanternLayer::OnAttach() {

		m_ActiveScene = Application::Get().m_ActiveScene;
		m_SceneState = SceneState::Edit;

		m_EntityListPanel = std::make_shared<EntityListPanel>(m_ActiveScene);
		m_AssetPanel = std::make_shared<AssetPanel>(m_ActiveScene);

		FramebufferSpecification spec;
		spec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::DEPTH24STENCIL8 };
		spec.Width = 1366;
		spec.Height = 768;
		m_Framebuffer = Framebuffer::Create(spec);

	}

	void LanternLayer::OnUpdate(DeltaTime dt) {

		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportPanelSize.x > 0.0f && m_ViewportPanelSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportPanelSize.x || spec.Height != m_ViewportPanelSize.y))
		{
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportPanelSize.x, (uint32_t)m_ViewportPanelSize.y);
			if(m_RuntimeScene)
				m_RuntimeScene->OnViewportResize((uint32_t)m_ViewportPanelSize.x, (uint32_t)m_ViewportPanelSize.y);
			m_Framebuffer->Resize((uint32_t)m_ViewportPanelSize.x, (uint32_t)m_ViewportPanelSize.y);
			m_LanternCamera.SetViewportSize((uint32_t)m_ViewportPanelSize.x, (uint32_t)m_ViewportPanelSize.y);

			// LanternCamera SetViewportSize doesn't recalculate viiewproj matrix
			// LanternCamera OnUpdate does
		}
		


		m_Framebuffer->Bind(); 
		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		RenderCommand::Clear();
		m_Framebuffer->ClearAttachment(1, -1);

		CalculateMousePos();

		switch (m_SceneState) {
		case SceneState::Edit:
		{
			m_LanternCamera.OnUpdate(dt, m_SceneMousePos);
			m_ActiveScene->OnUpdateEdit(dt, m_LanternCamera.GetViewProjection());
			break;
		}
		case SceneState::Pause:
		{
			m_LanternCamera.OnUpdate(dt, m_SceneMousePos);
			m_RuntimeScene->OnUpdateEdit(dt, m_LanternCamera.GetViewProjection());
			break;
		}
		case SceneState::Runtime:
		{
			m_RuntimeScene->OnUpdateRuntime(dt); 
			break;
		}
		}
			
		// Selecting entity
		if (m_ViewportMousePos.x >= 0 && m_ViewportMousePos.y >= 0 && m_ViewportMousePos.x < m_ViewportPanelSize.x && m_ViewportMousePos.y <= m_ViewportPanelSize.y) {
			int entityId = m_Framebuffer->ReadPixel(1, m_ViewportMousePos.x, m_ViewportMousePos.y);

			if (Input::IsMouseButtonPressed(RapierKey_MouseLeft)) {
				if (entityId == -1)
					m_ActiveScene->ClearSelectedEntities();
				else {
					Entity entity{ (entt::entity)(uint32_t)entityId, m_ActiveScene.get() };
					if(!Input::IsKeyPressed(RapierKey_LeftShift))
						m_ActiveScene->ClearSelectedEntities();
					m_ActiveScene->AddSelectedEntities(entity);
				}
			}
		}
        
		m_Framebuffer->Unbind();
	}


	void LanternLayer::OnImGuiRender() {


        static bool p_open = true;
        static bool opt_fullscreen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;


        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &p_open, window_flags);
        ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

		// Menu Bar
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Scene"))
					NewScene();
				
				if (ImGui::MenuItem("Save Scene"))
					SaveScene();
				
				if (ImGui::MenuItem("Load Scene"))
					LoadScene();
				
				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Editor"))
			{
				if (ImGui::MenuItem("Scene Editor"))
					RAPIER_CORE_INFO("Scene Editor");
				if (ImGui::MenuItem("Texture Editor"))
					RAPIER_CORE_INFO("Texture Editor");
				if (ImGui::MenuItem("Audio Editor"))
					RAPIER_CORE_INFO("Audio Editor");

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Scene"))
			{
				if (m_SceneState == SceneState::Runtime) {
					if (ImGui::MenuItem("Pause Scene"))
						PauseScene();
					if (ImGui::MenuItem("Stop Scene"))
						StopScene();
				}
				else {
					if (ImGui::MenuItem("Play Scene"))
						PlayScene();
				}

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

        ImGui::End();


		// Main viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
	    ImGui::Begin("Viewport");
		m_MainViewportFocused = ImGui::IsWindowFocused();
		m_MainViewportHovered = ImGui::IsWindowHovered();

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		ImVec2 windowPos = ImGui::GetWindowPos();
		m_ViewportPanelSize = { viewportPanelSize.x, viewportPanelSize.y };
		m_ViewportMinBound = { windowPos.x, windowPos.y };

		uint32_t textureId = m_Framebuffer->GetColorAttachmentRendererId(0);
		ImGui::Image((void*)textureId, viewportPanelSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		// Texture Drag And Drop
		if (m_SceneState == SceneState::Edit && ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TextureDND"))
			{
				const char* payloadData = (const char*)payload->Data;
				Entity entity = m_ActiveScene->CreateEntity();
				auto& transform = entity.GetComponent<TransformComponent>();
				entity.AddComponent<SpriteRendererComponent>(AssetManager::GetTexture2D(payloadData));

				transform.Rotation = m_LanternCamera.m_Rotation;

				transform.Translation.x = m_SceneMousePos.x;
				transform.Translation.y = m_SceneMousePos.y;
				
			}
			ImGui::EndDragDropTarget();
		}

	    ImGui::End();
		ImGui::PopStyleVar();


		Input::SetBlockKeyInput(!m_MainViewportFocused);
		Input::SetBlockMouseInput(!m_MainViewportHovered);
		
		m_EntityListPanel->OnImGuiRender();
		m_AssetPanel->OnImGuiRender();
	}

	void LanternLayer::NewScene() {
		m_ActiveScene = std::make_shared<Scene>();
		m_ActiveScene->OnViewportResize((uint32_t)m_ViewportPanelSize.x, (uint32_t)m_ViewportPanelSize.y);
		m_EntityListPanel->SetScene(m_ActiveScene);
		m_AssetPanel->SetScene(m_ActiveScene);
	}

	void LanternLayer::SaveScene() {
		std::string filepath = FileSystem::SceneSaveFileDialog();

		if (!filepath.empty()) {
			SceneSerializer serializer(m_ActiveScene);
			serializer.Serialize(filepath);
		}
	}

	void LanternLayer::LoadScene() {
		std::string filepath = FileSystem::SceneOpenFileDialog();

		if (!filepath.empty()) {
			Ref<Scene> newScene = std::make_shared<Scene>();

			SceneSerializer serializer(newScene);
			if (serializer.Deserialize(filepath)) {
				m_ActiveScene = newScene;
				m_ActiveScene->OnViewportResize((uint32_t)m_ViewportPanelSize.x, (uint32_t)m_ViewportPanelSize.y);
				m_EntityListPanel->SetScene(m_ActiveScene);
				m_AssetPanel->SetScene(m_ActiveScene);
			}
		}
	}


	void LanternLayer::CalculateMousePos() {

		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportMinBound.x;
		my -= m_ViewportMinBound.y;

		my = m_ViewportPanelSize.y - my;	
		
		m_ViewportMousePos.x = mx;
		m_ViewportMousePos.y = my;


		glm::vec2 vector = { 0.0f, 0.0f };
		glm::mat2x2 rot;

		if (m_SceneState == SceneState::Runtime) {

			auto primaryCamera = m_ActiveScene->GetPrimaryCamera();
			// if primary camera exists
			if ((uint32_t)primaryCamera != 0xffffffff) {
				auto primaryCameraTransform = primaryCamera.GetComponent<TransformComponent>();
				auto primaryCameraProjection = primaryCamera.GetComponent<CameraComponent>().Camera;
				vector = { primaryCameraProjection.GetSize() * primaryCameraProjection.GetAspectRatio() *
					(m_ViewportMousePos.x / m_ViewportPanelSize.x - 0.5f),
					primaryCameraProjection.GetSize() *
					(m_ViewportMousePos.y / m_ViewportPanelSize.y - 0.5f)
				};

				rot = { {glm::cos(glm::radians(primaryCameraTransform.Rotation.z)),
						 glm::sin(glm::radians(primaryCameraTransform.Rotation.z))},
						{-glm::sin(glm::radians(primaryCameraTransform.Rotation.z)),
						 glm::cos(glm::radians(primaryCameraTransform.Rotation.z))} };

				vector = rot * vector;
				vector.x += primaryCameraTransform.Translation.x;
				vector.y += primaryCameraTransform.Translation.y;

			}
		}
		else {
			vector = { m_LanternCamera.GetSize() * m_LanternCamera.GetAspectRatio() *
				(m_ViewportMousePos.x / m_ViewportPanelSize.x - 0.5f),
				m_LanternCamera.GetSize() *
				(m_ViewportMousePos.y / m_ViewportPanelSize.y - 0.5f)
			};

			rot = { {glm::cos(glm::radians(m_LanternCamera.m_Rotation.z)),
					 glm::sin(glm::radians(m_LanternCamera.m_Rotation.z))},
					{-glm::sin(glm::radians(m_LanternCamera.m_Rotation.z)),
					 glm::cos(glm::radians(m_LanternCamera.m_Rotation.z))} };

			vector = rot * vector;
			vector.x += m_LanternCamera.m_Translation.x;
			vector.y += m_LanternCamera.m_Translation.y;

		}

		m_SceneMousePos = vector;

	}


	void LanternLayer::PlayScene() {
		if(!m_RuntimeScene)
			m_RuntimeScene = Scene::Copy(m_ActiveScene);
		
		m_EntityListPanel->SetScene(m_RuntimeScene);
		m_AssetPanel->SetScene(m_RuntimeScene);
		m_SceneState = SceneState::Runtime;
	}

	void LanternLayer::PauseScene() {
		m_SceneState = SceneState::Pause;
	}

	void LanternLayer::StopScene() {
		m_EntityListPanel->SetScene(m_ActiveScene);
		m_AssetPanel->SetScene(m_ActiveScene);
		m_RuntimeScene = nullptr;
		m_SceneState = SceneState::Edit;
	}


	bool LanternLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e) {
		if (!m_MainViewportHovered) return true;
		return false;
	}

	bool LanternLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e) {
		if (!m_MainViewportHovered) return true;
		return false;
	}

	bool LanternLayer::OnMouseMovedEvent(MouseMovedEvent& e) {
		if (!m_MainViewportHovered)  return true;
		return false;
	}

	bool LanternLayer::OnMouseScrolledEvent(MouseScrolledEvent& e) {
		if (!m_MainViewportHovered)  return true;
		m_LanternCamera.OnMouseScrolledEvent(e);
		return false;
	}

	bool LanternLayer::OnKeyPressedEvent(KeyPressedEvent& e) {
		if (!m_MainViewportFocused)  return true;	
		return false;
	}

	bool LanternLayer::OnKeyReleasedEvent(KeyReleasedEvent& e) {
		if (!m_MainViewportFocused) return true;
		return false;
	}

	bool LanternLayer::OnKeyTypedEvent(KeyTypedEvent& e) {
		if (!m_MainViewportFocused) return true;
		return false;
	}

	bool LanternLayer::OnWindowResizeEvent(WindowResizeEvent& e) {
		return false;
	}

}