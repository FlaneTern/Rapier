#include "Layer/LanternLayer.h"
#include "RapierLantern.h"
#include "LanternCamera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"



namespace Rapier {

	void LanternLayer::OnUpdate(DeltaTime dt) {


		if (FramebufferSpecification spec = m_Framebuffer->GetSpecification();
			m_ViewportPanelSize.x > 0.0f && m_ViewportPanelSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != m_ViewportPanelSize.x || spec.Height != m_ViewportPanelSize.y))
		{
			m_ActiveScene->OnViewportResize((uint32_t)m_ViewportPanelSize.x, (uint32_t)m_ViewportPanelSize.y);
			m_Framebuffer->Resize((uint32_t)m_ViewportPanelSize.x, (uint32_t)m_ViewportPanelSize.y);
		}
		


		m_Framebuffer->Bind(); 
		RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		RenderCommand::Clear();
		m_Framebuffer->ClearAttachment(1, -1);
		m_ActiveScene->OnUpdate(dt);		


		// Mouse positions
		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_ViewportMinBound.x;
		my -= m_ViewportMinBound.y;

		my = m_ViewportPanelSize.y - my;

		// Selecting entity
		if (mx >= 0 && my >= 0 && mx < m_ViewportPanelSize.x && my <= m_ViewportPanelSize.y) {
			int entityId = m_Framebuffer->ReadPixel(1, mx, my);
			RAPIER_CORE_INFO("POS : {0}, {1}, {2}", mx, my, entityId);

			if (Input::IsMouseButtonPressed(RapierKey_MouseLeft)) {
				if (entityId == -1)
					m_ActiveScene->ClearSelectedEntities();
				else {
					if(!Input::IsKeyPressed(RapierKey_LeftShift))
						m_ActiveScene->ClearSelectedEntities();
					m_ActiveScene->AddSelectedEntities(entityId);
				}
			}
		}
        
		m_Framebuffer->Unbind();
	}

	void LanternLayer::OnAttach() {

		m_ActiveScene = Application::Get().m_ActiveScene;


		//////////////////////////////////////////////////////////////// TESTING ////////////////////////////////////////////////////////////////

		FramebufferSpecification spec;
		spec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::DEPTH24STENCIL8 };
		spec.Width = 1366;
		spec.Height = 768;
		m_Framebuffer = Framebuffer::Create(spec);


		class TextureControl : public EntityScript {
			float RotationSpeed  = 135.0f;
			float TranslationSpeed  = 2.0f;


			virtual void OnUpdate(DeltaTime dt) override {

				auto& transform = GetComponent<TransformComponent>();

				transform.Rotation.z += RotationSpeed * dt;
				if (transform.Rotation.z >= 360.0f)
					transform.Rotation.z -= 360.0f;
				

				if (Input::IsKeyPressed(RapierKey_W)) transform.Translation.y += TranslationSpeed * dt;
				if (Input::IsKeyPressed(RapierKey_S)) transform.Translation.y -= TranslationSpeed * dt;
				if (Input::IsKeyPressed(RapierKey_D)) transform.Translation.x += TranslationSpeed * dt;
				if (Input::IsKeyPressed(RapierKey_A)) transform.Translation.x -= TranslationSpeed * dt;
			}
		};

		class SquareControlX : public EntityScript {
			bool forward = true;

			virtual void OnUpdate(DeltaTime dt) override {
				auto& transform = GetComponent<TransformComponent>();
				float& x = transform.Translation.x;

				if (x > 3.0f) 
					forward = false;
				else if (x < -3.0f) 
					forward = true;


				if (forward) 
					x += 3.0f * dt;
				else 
					x -= 3.0f * dt;
			}
		};


		class SquareControlY : public EntityScript {
			bool forward = true;

			virtual void OnUpdate(DeltaTime dt) override {
				auto& transform = GetComponent<TransformComponent>();
				float& y = transform.Translation.y;

				if (y > 3.0f) 
					forward = false;
				else if (y < -3.0f) 
					forward = true;


				if (forward) 
					y += 3.0f * dt;
				else 
					y -= 3.0f * dt;
			}
		};

		auto squarex = m_ActiveScene->CreateEntity("Square X");
		squarex.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f });
		squarex.AddComponent<NativeScriptComponent>().Bind<SquareControlX>();

		auto squarey = m_ActiveScene->CreateEntity("Square Y");
		squarey.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.3f, 0.2f, 1.0f });
		squarey.AddComponent<NativeScriptComponent>().Bind<SquareControlY>();

		auto texture = m_ActiveScene->CreateEntity("Texture");
		texture.AddComponent<SpriteRendererComponent>(AssetManager::GetTexture2D("irene-gyatekora-v1.png"));
		texture.AddComponent<NativeScriptComponent>().Bind<TextureControl>();


		Entity cameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
		float l = -16.0f * 3.0f / 9.0f, r = 16.0f * 3.0f / 9.0f, b = -1.0f * 3.0f, t = 1.0f * 3.0f, f = -1000.0f, n = 1000.0f;
		auto& cameraComponent = cameraEntity.AddComponent<CameraComponent>(l, r, b, t, f, n);
		cameraComponent.Primary = true;
		cameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		

		//////////////////////////////////////////////////////////////// TESTING ////////////////////////////////////////////////////////////////
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
	    ImGui::End();
		ImGui::PopStyleVar();

		Input::SetBlockKeyInput(!m_MainViewportFocused);
		Input::SetBlockMouseInput(!m_MainViewportHovered);
		
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