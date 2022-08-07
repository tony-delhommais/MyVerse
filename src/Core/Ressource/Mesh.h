//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MESH_H
#define MYVERSE_MESH_H

#include "Core/Utils/Utils.h"
#include "Core/Utils/JsonUtils.h"
#include "Core/Utils/MathUtils.h"
#include "Core/Utils/GraphicsUtils.h"

#ifdef _DEBUG
#include "Core/Debug.h"
#endif

namespace Core
{

#pragma pack(push, 1)

	struct VertexDescriptor
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoords;
	};

	typedef glm::ivec3 FaceDescriptor;

#pragma pack(pop)


	class Mesh
	{
	public:
		Mesh() = default;
		~Mesh();

		static std::vector<std::shared_ptr<Mesh>> LoadFromOBJ(const std::filesystem::path& p_path);
		static std::shared_ptr<Mesh> LoadFromChunckData(JsonObject& p_chunckData);

		void RenderMesh();

	private:
		bool GenerateVBO();

		std::vector<VertexDescriptor> m_vertices;
		std::vector<FaceDescriptor>	m_faces;
		unsigned int m_nbFaces = 0;

		GLuint m_VBO_id = 0;
		GLuint m_EBO_id = 0;
	};

} // Core

#endif // MYVERSE_MESH_H
