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

	class RAPIER_API FileSystem {

	public:

		static void Init();

		static std::pair<std::string, std::string> GetDataShader(const std::string& filename);
		static Ref<TextureData> GetDataTexture(const std::string& filename);

		static void RefreshTextureDirectory();
		static void RefreshShaderDirectory();

		static bool IsDirectory(const std::string& name);
		static bool IsTexture(const std::string& name);
		static bool IsShader(const std::string& name);


		// Platform dependent //////////////////
		static std::string OpenFileDialog(const std::string& filter);
		static std::string SaveFileDialog(const std::string& filter);

		static void* LoadDLL(const std::string& filename);
		static void* LoadDLLFunction(void* DLLHandle, const std::string& functionName);
		static bool UnloadDLL(void* handle);


	private:
		static std::vector<std::string> s_TextureDirectoryEntries;
		static std::vector<std::string> s_ShaderDirectoryEntries;

		static void* s_ScriptHandle;

		friend class AssetManager;
		friend class AssetPanel;
	};

}