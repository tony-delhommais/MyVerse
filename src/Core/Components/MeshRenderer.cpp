//
// Created by Tony on 29/06/2022.
//

#include "Core/Components/MeshRenderer.h"

#include "Core/Managers/RessourceManager.h"

#include "Core/Ressource/Mesh.h"
#include "Core/Ressource/Material.h"

namespace Core
{

	std::shared_ptr<MeshRenderer> MeshRenderer::Make(JsonObject& p_componentProprety)
	{
		if (GetParameterFromJsonObject(p_componentProprety, "Type", "Null") != "MeshRenderer")
		{
			return nullptr;
		}

		std::string mesh_uuid = GetParameterFromJsonObject(p_componentProprety, "Mesh", "Null");
		if (mesh_uuid == "Null")
		{
#ifdef _DEBUG
			Debug::LogWarning("[MeshFactory] UUID is invalid");
#endif
			return nullptr;
		}

		auto uuid = UUIDv4::UUID::fromStrFactory(mesh_uuid);

		auto meshRenderer = std::make_shared<MeshRenderer>();

		meshRenderer->m_meshesUuid = uuid;

		auto materialParametersList = GetParameterFromJsonObject(p_componentProprety, "Materials", true, false);
		if (materialParametersList != p_componentProprety)
		{
			for (auto& materialParameters : materialParametersList)
			{
				int linkId = GetParameterFromJsonObject(materialParameters, "LinkId", 0);

				auto material_uuid = GetParameterFromJsonObject(materialParameters, "Uuid", "Null");
				if (material_uuid == "Null") continue;
				uuid = UUIDv4::UUID::fromStrFactory(material_uuid);

				meshRenderer->m_usedMaterialsUuid.insert(std::map<int, UUIDv4::UUID>::value_type(linkId, uuid));
			}
		}
		std::string shaderUuid = "63101c80-44b9-4554-a848-5963002a864b";
		meshRenderer->m_shaderUuid = UUIDv4::UUID::fromStrFactory(shaderUuid);

		return meshRenderer;
	}

	void MeshRenderer::FindMeshRef()
	{
		SetMeshes(RessourceManager::FindMeshes(m_meshesUuid));
	}

	void MeshRenderer::FindMaterialRef(int p_meshId)
	{
		auto materialMap = m_usedMaterialsUuid.find(p_meshId);

		if (materialMap == m_usedMaterialsUuid.end()) return;

		auto material = RessourceManager::FindMaterial(materialMap->second);

		SetRenderMaterial(material, p_meshId);
	}

	void MeshRenderer::Render(const glm::mat4& p_MVP)
	{
		if (m_shader)
		{
			m_shader->Use();
			m_shader->SetUniformMat4("MVP", p_MVP);
		}
		else
		{
			m_shader = RessourceManager::FindShader(m_shaderUuid);
		}

		if (m_meshesMaterials.empty())
		{
			FindMeshRef();
		}

		if(!m_meshesMaterials.empty())
		{
			int meshId = 0;
			for (auto& link : m_meshesMaterials)
			{
				if (link.mesh)
				{
					if (!link.material)
						FindMaterialRef(meshId);

					if (link.material)
						link.material->Use(m_shader);

					link.mesh->RenderMesh();

					if (link.material)
						link.material->NotUse();
				}

				meshId++;
			}
		}
	}

	void MeshRenderer::SetMeshes(std::vector<std::shared_ptr<Mesh>> p_meshes)
	{
		if (p_meshes.empty()) return;

		m_meshesMaterials.clear();

		for (auto& mesh : p_meshes)
		{
			LinkMeshMaterial link;

			link.mesh = mesh;

			m_meshesMaterials.push_back(link);
		}
	}

	void MeshRenderer::SetRenderMaterial(std::shared_ptr<Material> p_material, int p_assignedMeshPos)
	{
		if (p_assignedMeshPos < 0 || p_assignedMeshPos >= m_meshesMaterials.size())
			return;

		m_meshesMaterials[p_assignedMeshPos].material = p_material;
	}

	int MeshRenderer::GetMeshesCount()
	{
		return int(m_meshesMaterials.size());
	}

} // Core
