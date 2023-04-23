#include "ipch.h"

#include "Platform/OpenGL/OpenGLTexture.h"
#include "FileSystem/FileSystem.h"

#include "glad/glad.h"

namespace Rapier {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
	{
		Ref<TextureData> data = FileSystem::GetDataTexture(path);
		m_Filepath = path;

		m_Width = data->Width;
		m_Height = data->Height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererId);
		glTextureStorage2D(m_RendererId, 1, GL_RGB8, m_Width, m_Height);

		glTextureParameteri(m_RendererId, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererId, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



		// temp //////////////////////////////////////////////////////////////////////////////////////
		int channels;
		switch (data->Channels) {
		case 1: channels = GL_ALPHA; break;
		case 2: channels = GL_RG; break;
		case 3: channels = GL_RGB; break;
		case 4: channels = GL_RGBA; break;
		default: channels = 0; RAPIER_CORE_ASSERT(false, "Unknown channel!");
		}
		//////////////////////////////////////////////////////////////////////////////////////////////
		
		glTextureSubImage2D(m_RendererId, 0, 0, 0, m_Width, m_Height, channels, GL_UNSIGNED_BYTE, data->Data.data());



		///////////////////////////////////////////
		free((void*)data->Data.data());
		///////////////////////////////////////////
	}

	OpenGLTexture2D::~OpenGLTexture2D() {
		glDeleteTextures(1, &m_RendererId);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const {
		glBindTextureUnit(slot, m_RendererId);
	}
}