#include "ipch.h"
#include "FileSystem/FileSystem.h"
#include "stb_image.h"

namespace Rapier {

	Scope<FileSystem> FileSystem::s_Instance = std::make_unique<FileSystem>();

	Ref<std::string> FileSystem::GetDataShader(const std::string& filepath) {
		std::fstream stream(filepath);

		RAPIER_CORE_ASSERT(stream.is_open(), "Could not open file!");

		std::stringstream ss;
		ss << stream.rdbuf();
		Ref<std::string> data = std::make_shared<std::string>(ss.str());

		return data;
	}

	Ref<TextureData> FileSystem::GetDataTexture(const std::string& filepath) {
		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;


		///// !!!!!!!!!!!!!!!!!!!!!! free the data !!!!!!!!!!!!!!!!!!!!!!!!!!! /////
		stbi_uc* stbiData = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		///// !!!!!!!!!!!!!!!!!!!!!! free the data !!!!!!!!!!!!!!!!!!!!!!!!!!! /////

		RAPIER_CORE_ASSERT(stbiData, "Could not open file!");

		Ref<TextureData> data = std::make_shared<TextureData>((char*)stbiData, width, height, channels);

		return data;
	}




}