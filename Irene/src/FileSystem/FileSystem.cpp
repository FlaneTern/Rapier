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

	std::shared_ptr<std::string> FileSystem::GetDataShader(const std::string& filepath) {
		m_Filepath = filepath;
		m_Stream.reset(new std::fstream(filepath));

		IRENE_CORE_ASSERT(m_Stream->is_open(), "Could not open file!");

		std::stringstream ss;
		ss << m_Stream->rdbuf();
		std::shared_ptr<std::string> data = std::make_shared<std::string>(ss.str());

#ifdef IRENE_DEBUG
		m_Buffers.push_back(data);
#endif
		return data;
	}

#ifdef IRENE_DEBUG
	void FileSystem::ClearBuffers() {
		for (auto it = m_Buffers.begin(); it < m_Buffers.end(); it++) {
			if (it->use_count() == 1) {
				m_Buffers.erase(it);
				it--;
			}
		}
	}
#endif


}