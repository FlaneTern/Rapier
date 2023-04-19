#include "ipch.h"
#include "FileSystem/FileSystem.h"
#include "stb_image.h"

namespace Rapier {

	Ref<std::string> FileSystem::GetDataShader(const std::string& filepath) {
		std::string file = "";
		for (const auto& entry : std::filesystem::recursive_directory_iterator("../Rapier/res/Shader/")) {
			if (entry.path().filename() == filepath) {
				file = entry.path().string();
				break;
			}
		}
		RAPIER_CORE_ASSERT(!file.empty(), "Could not open file!");


		std::fstream stream(file);
		std::stringstream ss;
		ss << stream.rdbuf();
		Ref<std::string> data = std::make_shared<std::string>(ss.str());

		return data;
	}

	Ref<TextureData> FileSystem::GetDataTexture(const std::string& filepath) {
		std::string file = "";
		for (const auto& entry : std::filesystem::recursive_directory_iterator("../Rapier/res/Texture/")) {
			if (entry.path().filename() == filepath) {
				file = entry.path().string();
				break;
			}
		}
		RAPIER_CORE_ASSERT(!file.empty(), "Could not open file!");


		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;

		///// !!!!!!!!!!!!!!!!!!!!!! free the data !!!!!!!!!!!!!!!!!!!!!!!!!!! /////
		stbi_uc* stbiData = stbi_load(file.c_str(), &width, &height, &channels, 0);
		///// !!!!!!!!!!!!!!!!!!!!!! free the data !!!!!!!!!!!!!!!!!!!!!!!!!!! /////


		Ref<TextureData> data = std::make_shared<TextureData>((char*)stbiData, width, height, channels);

		return data;
	}




}