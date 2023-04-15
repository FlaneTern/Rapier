#include "ipch.h"
#include "FileSystem/FileSystem.h"

namespace IRENE {

	std::unique_ptr<FileSystem> FileSystem::s_Instance = std::make_unique<FileSystem>();

	std::shared_ptr<std::string> FileSystem::GetData(const std::string& filepath, FileType type) {
		switch (type) {
		case FileType::Shader:   return s_Instance->GetDataShader(filepath);
		}
		

		IRENE_CORE_ASSERT(false, "Unknown file type!");
		return nullptr;
	}

	std::shared_ptr<std::string> FileSystem::GetDataShader(const std::string& filepath)
	{
		m_Filepath = filepath;
		m_Stream.reset(new std::fstream(filepath));

		IRENE_CORE_ASSERT(m_Stream->is_open(), "Could not open file!");

		std::shared_ptr<std::string> data = std::make_shared<std::string>();
		std::string temp;
		while (getline(*m_Stream, temp)) {
			*data += temp + '\n';
		}
		data->pop_back();

		return data;
	}


}