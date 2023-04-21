#include "Layer/LanternLayer.h"
#include "Geometry/Pentagon.h"
#include "RapierLantern.h"
#include "LanternCamera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"



namespace Rapier {

	void LanternLayer::OnUpdate(DeltaTime dt) {

		m_Framebuffer->Bind(); 

        RenderCommand::Clear();
		m_ActiveScene->OnUpdate(dt);


		/*Renderer2D::DrawCircle({ 0.0f, 0.0f, 0.0f }, { 3.0f, 3.0f }, { 1.0f, 0.5f, 1.0f, 1.0f });
		Renderer2D::DrawQuad({ -x, -y }, { width, height }, { 1.0f, 0.0f, 0.0f, 1.0f }, rotation);
		Renderer2D::DrawQuad({  x, -y }, { width, height }, { 0.0f, 0.0f, 1.0f, 1.0f }, rotation);
		Renderer2D::DrawQuad({ -x,  y }, { width, height }, { 0.0f, 1.0f, 0.0f, 1.0f }, rotation);
		Renderer2D::DrawQuad({  x,  y }, { width, height }, { 0.5f, 0.5f, 0.5f, 1.0f }, rotation);
        Renderer2D::DrawTexture({ xT, yT, 0.0f }, { widthT, heightT }, AssetManager::DefaultTexture2DId::IreneGyatekora3, rotationT);*/
		
        
		m_Framebuffer->Unbind();
	}

	void LanternLayer::OnAttach() {

		m_ActiveScene = Application::Get().m_ActiveScene;






		//////////////////////////////////////////////////////////////// TESTING ////////////////////////////////////////////////////////////////

		m_Texture = Texture2D::Create("irene-gyatekora-v1.png");
		//m_Texture = AssetManager::GetDefaultTexture2D(AssetManager::DefaultTexture2DId::IreneGyatekora2);
		FramebufferSpecification spec = { 1366, 768 };
		m_Framebuffer = Framebuffer::Create(spec);






		class TextureControl : public EntityScript {
			float RotationSpeed  = 135.0f;
			float TranslationSpeed  = 2.0f;


			virtual void OnUpdate(DeltaTime dt) override {

				auto& transform = GetComponent<TransformComponent>().Transform;
				transform = glm::rotate(transform, glm::radians(RotationSpeed * dt), glm::vec3(0, 0, 1));

				if (Input::IsKeyPressed(RapierKey_W)) transform[3][1] += TranslationSpeed * dt;
				if (Input::IsKeyPressed(RapierKey_S)) transform[3][1] -= TranslationSpeed * dt;
				if (Input::IsKeyPressed(RapierKey_D)) transform[3][0] += TranslationSpeed * dt;
				if (Input::IsKeyPressed(RapierKey_A)) transform[3][0] -= TranslationSpeed * dt;
			}
		};

		class SquareControlX : public EntityScript {
			float x = -2.0f;
			bool forward = true;


			virtual void OnUpdate(DeltaTime dt) override {

				if (x > 3.0f) 
					forward = false;
				else if (x < -3.0f) 
					forward = true;

				auto& transform = GetComponent<TransformComponent>().Transform;

				if (forward) 
					x += 3.0f * dt;
				else 
					x -= 3.0f * dt;
				transform[3][0] = x;
			}
		};


		class SquareControlY : public EntityScript {
			float y = -2.0f;
			bool forward = true;


			virtual void OnUpdate(DeltaTime dt) override {

				if (y > 3.0f) 
					forward = false;
				else if (y < -3.0f) 
					forward = true;

				auto& transform = GetComponent<TransformComponent>().Transform;

				if (forward) 
					y += 3.0f * dt;
				else 
					y -= 3.0f * dt;
				transform[3][1] = y;
			}
		};

		auto squarex = m_ActiveScene->CreateEntity("Square X");
		squarex.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f });
		squarex.AddComponent<NativeScriptComponent>().Bind<SquareControlX>();

		auto squarey = m_ActiveScene->CreateEntity("Square Y");
		squarey.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.8f, 0.3f, 0.2f, 1.0f });
		squarey.AddComponent<NativeScriptComponent>().Bind<SquareControlY>();

		auto texture = m_ActiveScene->CreateEntity("Texture");
		texture.AddComponent<SpriteRendererComponent>(m_Texture);
		texture.AddComponent<NativeScriptComponent>().Bind<TextureControl>();


		Entity cameraEntity = m_ActiveScene->CreateEntity("Camera Entity");
		float l = -16.0f * 3.0f / 9.0f, r = 16.0f * 3.0f / 9.0f, b = -1.0f * 3.0f, t = 1.0f * 3.0f, f = -1.0f, n = 1.0f;
		cameraEntity.AddComponent<CameraComponent>(l, r, b, t, f, n);
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

        ImGui::End();


		// Main viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0.0f, 0.0f });
	    ImGui::Begin("Viewport");
		m_MainViewportFocused = ImGui::IsWindowFocused();
		m_MainViewportHovered = ImGui::IsWindowHovered();
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (m_ViewportPanelSize != *(glm::vec2*)&viewportPanelSize) {
			m_Framebuffer->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			m_ViewportPanelSize = { viewportPanelSize.x, viewportPanelSize.y };
			m_ActiveScene->OnViewportResize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
		}
	    uint32_t textureId = m_Framebuffer->GetColorAttachmentRendererId();
        ImGui::Image((void*)textureId, ImVec2{ m_ViewportPanelSize.x, m_ViewportPanelSize.y }, ImVec2{0,1}, ImVec2{1,0});
	    ImGui::End();
		ImGui::PopStyleVar();
        
		
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