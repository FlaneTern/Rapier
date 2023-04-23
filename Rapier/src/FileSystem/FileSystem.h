#pragma once

namespace Rapier {

	enum class FileType {
		None = 0,
		Shader,
		Texture
	};

	struct TextureData {
		TextureData(const char* s, uint32_t w, uint32_t h, uint32_t ch)
			: Data(s), Width(w), Height(h), Channels(ch) {}

		std::string_view Data;
		uint32_t Width;
		uint32_t Height;
		uint32_t Channels;
	};

	class FileSystem {

	public:

		static void Init();

		static std::pair<std::string, std::string> GetDataShader(const std::string& filename);
		static Ref<TextureData> GetDataTexture(const std::string& filename);

		static void RefreshTextureDirectory();
		static void RefreshShaderDirectory();

		static bool IsDirectory(const std::string& name);
		static bool IsTexture(const std::string & name);
		static bool IsShader(const std::string & name);

	private:
		static std::vector<std::string> s_TextureDirectoryEntries;
		static std::vector<std::string> s_ShaderDirectoryEntries;
		friend class AssetManager;
		friend class AssetPanel;
	};

}