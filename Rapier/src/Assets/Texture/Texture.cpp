#include "ipch.h"

#include "Assets/Texture/Texture.h"

#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

#include "Assets/AssetManager.h"

namespace Rapier {
	Ref<Texture2D> Texture2D::Create(const std::string& filename) {
		return AssetManager::LoadTexture2D(filename);
	}
}