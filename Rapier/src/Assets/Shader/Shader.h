#pragma once
#include "ipch.h"
#include "glm/glm.hpp"

namespace Rapier {
	class Shader {
	public:

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void UploadUniformMat4(const std::string& name, const glm::mat4& matrix) = 0;
		virtual void UploadUniformInt(const std::string& name, int value) = 0;
		virtual void UploadUniformFloat4(const std::string& name, glm::vec4 value) = 0;
		virtual void UploadUniformIntArray(const std::string& name, int* value, uint32_t count) = 0;



		uint32_t GetAssetManagerId() { return m_AssetManagerId; }
		void SetAssetManagerId(uint32_t id) { m_AssetManagerId = id; }

		static Ref<Shader> Create(const std::string& filename);

	protected:
		RendererId m_RendererId;
		uint32_t m_AssetManagerId;
	};
}