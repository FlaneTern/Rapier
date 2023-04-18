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
		static Ref<std::string> GetDataShader(const std::string& filepath);
		static Ref<TextureData> GetDataTexture(const std::string& filepath);
	private:
		static Scope<FileSystem> s_Instance;

	};

}