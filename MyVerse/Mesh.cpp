//
// Created by Tony on 29/06/2022.
//

#include "Mesh.h"

#include "tiny_obj_loader.h"

namespace Client
{

	Mesh::~Mesh()
	{
		if (m_VAO_id)
			glDeleteVertexArrays(1, &m_VAO_id);
		if (m_VBO_id)
			glDeleteBuffers(1, &m_VBO_id);
		if (m_EBO_id)
			glDeleteBuffers(1, &m_EBO_id);

		m_vertices.clear();

		m_faces.clear();
	}

	std::vector<std::shared_ptr<Mesh>> Mesh::LoadFromOBJ(const std::filesystem::path& p_path)
	{
		tinyobj::ObjReader reader;
		reader.ParseFromFile(p_path.string());

		auto& shapes = reader.GetShapes();
		auto& attrib = reader.GetAttrib();

		std::vector<std::shared_ptr<Mesh>> meshes;

		for (size_t s = 0; s < shapes.size(); s++)
		{
			auto mesh = std::make_shared<Mesh>();

			size_t index_offset = 0;
			for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
			{
				size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

				for (size_t v = 0; v < fv; v++)
				{
					tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

					VertexDescriptor vd;

					vd.position.x = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
					vd.position.y = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
					vd.position.z = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

					if (idx.normal_index >= 0)
					{
						vd.normal.x = attrib.normals[3 * size_t(idx.normal_index) + 0];
						vd.normal.y = attrib.normals[3 * size_t(idx.normal_index) + 1];
						vd.normal.z = attrib.normals[3 * size_t(idx.normal_index) + 2];
					}

					if (idx.texcoord_index >= 0)
					{
						vd.texcoords0.x = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
						vd.texcoords0.y = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
					}

					mesh->m_vertices.push_back(vd);
				}

				index_offset += fv;

				mesh->m_faces.push_back(glm::ivec3(f * 3 + 0, f * 3 + 1, f * 3 + 2));
			}

			mesh->m_nbFaces = (unsigned int)(mesh->m_faces.size());

			if (!mesh->GenerateVBO())
			{
#ifdef _DEBUG
				Debug::LogError("Failed to generate VBO on a Mesh");
#endif
				return std::vector<std::shared_ptr<Mesh>>();
			}

			bool VAOGenerated = mesh->GenerateVAO();

#ifdef _DEBUG
			if (!VAOGenerated)
				Debug::LogWarning("Failed to generate VAO on a Mesh");
#endif

			meshes.push_back(mesh);
		}

		return meshes;
	}

	std::shared_ptr<Mesh> Mesh::LoadFromChunckData(JsonObject& p_chunckData)
	{
		JsonObject meshData = GetParameterFromJsonObject(p_chunckData, "Land", true, false);
		if(meshData == p_chunckData)
			return nullptr;

		auto mesh = std::make_shared<Mesh>();

		size_t faceVerticeId = 0;

		for (size_t i = 0; i < meshData.size(); i++)
		{
			VertexDescriptor vd;

			vd.position.x = meshData[i][0];
			vd.position.y = meshData[i][1];
			vd.position.z = meshData[i][2];

			mesh->m_vertices.push_back(vd);

			faceVerticeId++;
			if (faceVerticeId == 3)
			{
				mesh->m_faces.push_back(glm::ivec3(i - 2, i - 1, i - 0));

				faceVerticeId = 0;
				mesh->m_nbFaces++;
			}
		}

		if (!mesh->GenerateVBO())
		{
#ifdef _DEBUG
			Debug::LogError("Failed to generate VBO on a Mesh");
#endif
			return nullptr;
		}

		bool VAOGenerated = mesh->GenerateVAO();

#ifdef _DEBUG
		if (!VAOGenerated)
			Debug::LogWarning("Failed to generate VAO on a Mesh");
#endif

		return mesh;
	}

	void Mesh::RenderMesh()
	{
		if (m_VAO_id)
		{
			glBindVertexArray(m_VAO_id);

			glDrawElements(GL_TRIANGLES, m_nbFaces * 3, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
		}
		else if (m_VBO_id && m_EBO_id)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_id);

			OpenGLAttributesStride();

			glDrawElements(GL_TRIANGLES, m_nbFaces * 3, GL_UNSIGNED_INT, 0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}

	bool Mesh::GenerateVBO()
	{
		glGenBuffers(1, &m_VBO_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_id);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexDescriptor) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &m_EBO_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(FaceDescriptor) * m_faces.size(), m_faces.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		if (!m_VBO_id || !m_EBO_id)
			return false;

		m_vertices.clear();
		m_faces.clear();

		return true;
	}

	bool Mesh::GenerateVAO()
	{
		bool VBOGenerated = true;

		if (!m_VBO_id && !m_EBO_id)
			VBOGenerated = GenerateVBO();

		if (!VBOGenerated)
			return false;

		glGenVertexArrays(1, &m_VAO_id);
		if (!m_VAO_id)
			return false;

		glBindVertexArray(m_VAO_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_id);
		
		OpenGLAttributesStride();

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDeleteBuffers(1, &m_VBO_id);
		m_VBO_id = 0;
		glDeleteBuffers(1, &m_EBO_id);
		m_EBO_id = 0;

		return true;
	}

	void Mesh::OpenGLAttributesStride()
	{
		EnumAttrib attrib = EnumAttrib::POSITION;
		glEnableVertexAttribArray(attrib);
		glVertexAttribPointer(attrib, attribSize[attrib], GL_FLOAT, GL_FALSE, attribOffset[EnumAttrib::NB_ATTRIBUTES], (void*)(attribOffset[attrib]));

		attrib = EnumAttrib::NORMAL;
		glEnableVertexAttribArray(attrib);
		glVertexAttribPointer(attrib, attribSize[attrib], GL_FLOAT, GL_FALSE, attribOffset[EnumAttrib::NB_ATTRIBUTES], (void*)(attribOffset[attrib]));

		attrib = EnumAttrib::TEXCOORD0;
		glEnableVertexAttribArray(attrib);
		glVertexAttribPointer(attrib, attribSize[attrib], GL_FLOAT, GL_FALSE, attribOffset[EnumAttrib::NB_ATTRIBUTES], (void*)(attribOffset[attrib]));
	}

} // Client
