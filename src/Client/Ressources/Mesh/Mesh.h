//
// Created by Tony on 29/06/2022.
//

#ifndef MYVERSE_MESH_H
#define MYVERSE_MESH_H

#include "Client/Utils/Utils.h"
#include "Client/Utils/JsonUtils.h"
#include "Client/Utils/MathUtils.h"
#include "Client/Utils/GraphicsUtils.h"

#include "Client/Ressources/Shader/Shader.h"

#ifdef _DEBUG
#include "Client/Common/Debug.h"
#endif

namespace Client
{

#pragma pack(push, 1)

	struct VertexDescriptor
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoords0;
	};

	typedef glm::ivec3 FaceDescriptor;

#pragma pack(pop)


	const GLsizei attribOffset[EnumAttrib::NB_ATTRIBUTES + 1] = {
		0,							// POSITION
		sizeof(glm::vec3),			// NORMAL
		0,							// TANGENT
		0,							// BITANGENT
		0,							// COLOR
		sizeof(glm::vec3) * 2,		// TEXCOORD0
		0,							// TEXCOORD1
		0,							// TEXCOORD2
		0,							// TEXCOORD3
		sizeof(VertexDescriptor)	// STRIDE
	};

	const GLint attribSize[EnumAttrib::NB_ATTRIBUTES + 1] = {
		3,							// POSITION
		3,							// NORMAL
		3,							// TANGENT
		3,							// BITANGENT
		3,							// COLOR
		2,							// TEXCOORD0
		2,							// TEXCOORD1
		2,							// TEXCOORD2
		2,							// TEXCOORD3
		23							// STRIDE
	};


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
		bool GenerateVAO();

		void OpenGLAttributesStride();

		std::vector<VertexDescriptor> m_vertices;
		std::vector<FaceDescriptor>	m_faces;
		unsigned int m_nbFaces = 0;

		GLuint m_VBO_id = 0;
		GLuint m_EBO_id = 0;

		GLuint m_VAO_id = 0;
	};

} // Client

#endif // MYVERSE_MESH_H
