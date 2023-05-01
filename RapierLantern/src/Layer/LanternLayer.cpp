#include "Layer/LanternLayer.h"
#include "RapierLantern.h"
#include "Serializer/SceneSerializer.h"
#include "Assets/Script/Script.h"

#include "Gizmo/LanternGizmo.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"



namespace Rapier {

	void LanternLayer::OnAttach() {

		m_ActiveScene = std::make_shared<Scene>();
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

			// LanternCamera SetViewportSize doesn't recalculate viewproj matrix
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
			OnUpdateGizmos(dt);
			SelectEntity();
			
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
			
        
		m_Framebuffer->Unbind();
	}


	void LanternLayer::OnImGuiRender() {

		// Dockspace
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        
        ImGui::Begin("DockSpace Demo", (bool*)0, window_flags);
        ImGui::PopStyleVar(3);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
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
		if (m_SceneState == SceneState::Runtime)
			ImGui::SetNextWindowFocus();
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

	void LanternLayer::OnUpdateGizmos(DeltaTime dt) {
		if (LanternGizmo::s_GizmoEntities.empty())
			return;

		TIME_FUNCTION_INTERNAL(LanternLayer::OnUpdateGizmos);

		Renderer2D::BeginEditorRender(m_LanternCamera.GetViewProjection());


		switch (LanternGizmo::s_GizmoState) {
		case GizmoState::Translation:
		{
			auto data = LanternGizmo::GetRenderDataTranslation();
			Renderer2D::DrawTexture(data.TransformXQuad, nullptr, data.ColorX, -2);
			Renderer2D::DrawCircle(data.TransformXCircleEdge, nullptr, data.ColorX, -2);
			Renderer2D::DrawTexture(data.TransformYQuad, nullptr, data.ColorY, -3);
			Renderer2D::DrawCircle(data.TransformYCircleEdge, nullptr, data.ColorY, -3);
			Renderer2D::DrawCircle(data.TransformMidCircle, nullptr, data.ColorMidCircle, -4);

			break;
		}
		case GizmoState::Rotation:
		{
			auto data = LanternGizmo::GetRenderDataRotation();
			Renderer2D::DrawCircle(data.Transform, nullptr, data.Color, -2, 0.7f);
			break;
		}
		case GizmoState::Scale:
		{
			auto data = LanternGizmo::GetRenderDataScale();
			Renderer2D::DrawTexture(data.TransformXQuad, nullptr, data.ColorX, -2);
			Renderer2D::DrawTexture(data.TransformXQuadEdge, nullptr, data.ColorX, -2);
			Renderer2D::DrawTexture(data.TransformYQuad, nullptr, data.ColorY, -3);
			Renderer2D::DrawTexture(data.TransformYQuadEdge, nullptr, data.ColorY, -3);
			Renderer2D::DrawTexture(data.TransformMidQuad, nullptr, data.ColorMidQuad, -4);
			break;
		}
		}


		Renderer2D::EndEditorRender();


		LanternGizmo::OnUpdate(dt, m_LanternCamera, m_SceneMousePos, m_HoveredEntityId);

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
			if ((entt::entity)primaryCamera != entt::null) {
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

	void LanternLayer::SelectEntity() {

		if (Input::IsKeyPressed(RapierKey_Escape)) {
			m_ActiveScene->ClearSelectedEntities();
		}

		if (m_ViewportMousePos.x >= 0 && m_ViewportMousePos.y >= 0 && m_ViewportMousePos.x < m_ViewportPanelSize.x && m_ViewportMousePos.y <= m_ViewportPanelSize.y)
		{
			m_HoveredEntityId = m_Framebuffer->ReadPixel(1, m_ViewportMousePos.x, m_ViewportMousePos.y);

			if (Input::IsMouseButtonPressed(RapierKey_MouseLeft) && !Input::IsMouseButtonRepeat(RapierKey_MouseLeft))
			{
				if (m_HoveredEntityId < 0)
				{
					if (m_HoveredEntityId == -1)
					{
						LanternGizmo::ClearGizmo();
						m_ActiveScene->ClearSelectedEntities();
					}
				}
				else
				{
					Entity entity{ (entt::entity)m_HoveredEntityId, m_ActiveScene.get() };
					if (!Input::IsKeyPressed(RapierKey_LeftShift)) {
						LanternGizmo::ClearGizmo();
						m_ActiveScene->ClearSelectedEntities();
					}

					if (!m_ActiveScene->IsEntitySelected(entity)) 
					{
						LanternGizmo::CreateGizmo(entity);
						m_ActiveScene->AddSelectedEntities(entity);
					}
				}

			}
		}
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
				LanternGizmo::ClearGizmo();
			}
		}
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
		LanternGizmo::OnKeyReleasedEvent(e);
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