//
// Created by Tony on 29/06/2022.
//

#include "Core/Ressource/Mesh.h"

#include "OBJ_Loader.h"

namespace Core
{

	Mesh::Mesh(std::shared_ptr<Mesh> p_mesh)
	{
		m_vertices = p_mesh->m_vertices;
		m_faces = p_mesh->m_faces;
		m_nbFaces = p_mesh->m_nbFaces;

		GenerateVBO();
	}

	Mesh::~Mesh()
	{
		if (m_VBO_id) glDeleteBuffers(1, &m_VBO_id);
		if (m_EBO_id) glDeleteBuffers(1, &m_EBO_id);

		m_vertices.clear();

		m_faces.clear();
	}

	std::vector<std::shared_ptr<Mesh>> Mesh::LoadFromOBJ(const std::string& p_path)
	{
		objl::Loader loader;
		bool isLoaded = loader.LoadFile(p_path);

		std::vector<std::shared_ptr<Mesh>> meshes;

		for (size_t i = 0; i < loader.LoadedMeshes.size(); i++)
		{
			auto mesh = std::make_shared<Mesh>();

			size_t faceVerticeId = 0;
			for (size_t j = 0; j < loader.LoadedMeshes[i].Indices.size(); j++)
			{
				VertexDescriptor vd;

				size_t indiceId = loader.LoadedMeshes[i].Indices[j];

				auto vertice = loader.LoadedMeshes[i].Vertices[indiceId];

				vd.position.x = vertice.Position.X;
				vd.position.y = vertice.Position.Y;
				vd.position.z = vertice.Position.Z;

				vd.normal.x = vertice.Normal.X;
				vd.normal.y = vertice.Normal.Y;
				vd.normal.z = vertice.Normal.Z;

				vd.texcoords.x = vertice.TextureCoordinate.X;
				vd.texcoords.y = vertice.TextureCoordinate.Y;

				mesh->m_vertices.push_back(vd);

				faceVerticeId++;
				if (faceVerticeId == 3)
				{
					mesh->m_faces.push_back(glm::ivec3(j - 2, j - 1, j - 0));

					faceVerticeId = 0;
				}
			}

			mesh->m_nbFaces = (unsigned int)(mesh->m_faces.size());

			if (!mesh->GenerateVBO())
			{
#ifdef _DEBUG
				Debug::LogWarning("Failed to generate VBO on a Mesh");
#endif
				return std::vector<std::shared_ptr<Mesh>>();
			}

			meshes.push_back(mesh);
		}

		return meshes;
	}

	void Mesh::RenderMesh()
	{
		if (m_VBO_id && m_EBO_id)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO_id);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO_id);

			int stride = sizeof(VertexDescriptor);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(VertexDescriptor::position)));

			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(VertexDescriptor::position) + sizeof(VertexDescriptor::normal)));

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

		if (!m_VBO_id || !m_EBO_id) return false;

		m_vertices.clear();
		m_faces.clear();

		return true;
	}

} // Core
