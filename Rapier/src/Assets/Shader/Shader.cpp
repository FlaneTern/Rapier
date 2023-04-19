#include "ipch.h"
#include "Assets/Shader/Shader.h"
#include "Renderer/Renderer.h"
#include "Assets/AssetManager.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Rapier {
	Ref<Shader> Shader::Create(const std::string& vertexName, const std::string& fragmentName) {
		return AssetManager::LoadShader(vertexName, fragmentName);
	}
}