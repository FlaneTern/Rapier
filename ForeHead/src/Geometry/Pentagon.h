#pragma once
#include <vector>
#include <memory>
#include "glm/glm.hpp"

namespace Forehead {

	class Pentagon {

	public:

		inline float* GetVertices() { return m_Vertices.data(); }
		inline int GetVerticesSize() const { return (int)(m_Vertices.size() * sizeof(float)); }


		inline uint32_t* GetIndices() { return m_Indices.data(); }
		inline int GetIndicesSize() const { return (int)(m_Indices.size() * sizeof(int)); }

		static std::unique_ptr<Pentagon> s_Pentagon;

	private:
		std::vector<float> m_Vertices = {
			-0.5f,  -0.5f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
			 0.5f,  -0.5f,  0.0f, 0.8f, 0.8f, 0.8f, 1.0f,
			 0.75f,  0.3f,  0.0f, 0.0f, 0.0f, 0.5f, 1.0f,
			 0.0f,   0.9f,  0.0f, 0.0f, 0.5f, 0.0f, 1.0f,
			-0.75f,  0.3f,  0.0f, 0.5f, 0.0f, 0.0f, 1.0f
		};

		std::vector<uint32_t> m_Indices = { 0, 1, 2, 2, 3, 4, 0, 2, 4 };

	};
}