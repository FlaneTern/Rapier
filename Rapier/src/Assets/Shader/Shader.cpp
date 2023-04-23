#include "ipch.h"
#include "Assets/Shader/Shader.h"
#include "Renderer/Renderer.h"
#include "Assets/AssetManager.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Rapier {
	Ref<Shader> Shader::Create(const std::string& filename) {
		return AssetManager::LoadShader(filename);
	}
}