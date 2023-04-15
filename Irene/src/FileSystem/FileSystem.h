#pragma once
#include "ipch.h"

namespace IRENE {

	enum class FileType {
		None = 0,
		Shader
	};

	class FileSystem {

	public:
		static std::shared_ptr<std::string> GetData(const std::string& filepath, FileType type);

		std::shared_ptr<std::string> GetDataShader(const std::string& filepath);
	private:
		static std::unique_ptr<FileSystem> s_Instance;

		std::unique_ptr<std::fstream> m_Stream;
		std::string m_Filepath;

	};

}