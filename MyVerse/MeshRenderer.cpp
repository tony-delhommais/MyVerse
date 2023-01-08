//
// Created by Tony on 29/06/2022.
//

#include "MeshRenderer.h"

#include "Mesh.h"
#include "Material.h"

namespace Client
{

	MeshRenderer::MeshRenderer(std::shared_ptr<Entity> p_entity, std::vector<std::shared_ptr<Mesh>> p_subMeshes, std::vector<std::shared_ptr<Material>> p_materials) :
		Component(ComponentType::MESH_RENDERER, p_entity),
		m_subMeshes(p_subMeshes),
		m_materials(p_materials)
	{
		if (p_subMeshes.size() != p_materials.size())
		{
			Debug::LogError("[MeshRenderer] SubMeshes and Materials count are not the same");
		}
	}

	void MeshRenderer::Render()
	{
		for (int i = 0; i < m_subMeshes.size() && i < m_materials.size(); i++)
		{
			m_materials[i]->Use();

			m_subMeshes[i]->RenderMesh();

			m_materials[i]->Unuse();
		}
	}

} // Client
