//
// Created by Tony on 08/11/2022.
//

#include "Client/Components/MeshRenderer/MeshRendererBuilder.h"

#include "Client/Common/RessourceManager.h"

namespace Client
{

	std::shared_ptr<MeshRenderer> MeshRendererBuilder::Build()
	{
		if (m_subMeshes.empty())
			return nullptr;

		if (m_subMeshes.size() != m_materials.size())
		{
			m_materials.resize(m_subMeshes.size(), RessourceManager::FindMaterial(UUIDv4::UUID::fromStrFactory("Default")));
		}

		return std::make_shared<MeshRenderer>(m_entity, m_subMeshes, m_materials);
	}

	MeshRendererBuilder& MeshRendererBuilder::SetSubMeshes(std::vector<std::shared_ptr<Mesh>> p_subMeshes)
	{
		m_subMeshes = p_subMeshes;

		return *this;
	}

	MeshRendererBuilder& MeshRendererBuilder::SetMaterials(std::vector<std::shared_ptr<Material>> p_materials)
	{
		m_materials = p_materials;

		return *this;
	}

} // Client
