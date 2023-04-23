#include "ipch.h"
#include "FileSystem/FileSystem.h"
#include "stb_image.h"

namespace Rapier {

	std::vector<std::string> FileSystem::s_TextureDirectoryEntries;
	std::vector<std::string> FileSystem::s_ShaderDirectoryEntries;

	void FileSystem::Init() {
		// Implement recursive on Init !!!!!!!!!!!//////////
		// Implement recursive on Init !!!!!!!!!!!//////////
		// Implement recursive on Init !!!!!!!!!!!//////////
		RefreshTextureDirectory();
		RefreshShaderDirectory();
	}

	std::pair<std::string, std::string> FileSystem::GetDataShader(const std::string& filename) {
		std::string file = "";
		for (const auto& entry : std::filesystem::recursive_directory_iterator("../Rapier/res/Shader/")) {
			if (entry.path().filename() == filename) {
				file = entry.path().string();
				break;
			}
		}
		RAPIER_CORE_ASSERT(!file.empty(), "Could not open file!");


		std::stringstream vs;
		std::stringstream fs;
		std::fstream stream(file);
		std::string temp;
		while (getline(stream, temp)) {
			if (temp == "//START VERTEX") break;
		}

		while (getline(stream, temp)) {
			if (temp == "//START FRAGMENT") break;
			vs << temp << "\n";
		}

		while (getline(stream, temp)) {
			fs << temp << "\n";
		}

		std::pair<std::string, std::string> data = { vs.str(), fs.str() };

		return data;
	}

	Ref<TextureData> FileSystem::GetDataTexture(const std::string& filename) {
		std::string file = "";
		for (const auto& entry : std::filesystem::recursive_directory_iterator("../Rapier/res/Texture/")) {
			if (entry.path().filename() == filename) {
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

	bool FileSystem::IsDirectory(const std::string& name) {
		return name.back() == '/';
	}

	bool FileSystem::IsTexture(const std::string& name) {
		return name.substr(name.size() - 4, 4) == ".png";
	}

	bool FileSystem::IsShader(const std::string& name) {
		return name.substr(name.size() - 8, 8) == ".rshader";
	}

	void FileSystem::RefreshTextureDirectory() {
		s_TextureDirectoryEntries.clear();
		for (const auto& entry : std::filesystem::directory_iterator("../Rapier/res/Texture/")) {
			s_TextureDirectoryEntries.push_back(entry.path().filename().string());
		}
	}

	void FileSystem::RefreshShaderDirectory() {
		s_ShaderDirectoryEntries.clear();
		for (const auto& entry : std::filesystem::directory_iterator("../Rapier/res/Shader/")) {
			s_ShaderDirectoryEntries.push_back(entry.path().filename().string());
		}
	}
}